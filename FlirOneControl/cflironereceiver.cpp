//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cflironereceiver.h"
#include "clog.h"
#include <stdio.h>
#include <memory.h>

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CFlirOneReceiver::CFlirOneReceiver(void)
{ 
 size_t n;
 ThermalImage=new uint16_t[THERMAL_IMAGE_SIZE_SHORT];
 ColorImage=new uint32_t[COLOR_IMAGE_SIZE_LONG];
 VideoImage=new uint32_t[VIDEO_IMAGE_SIZE_LONG];

 for(n=0;n<IMAGE_WIDTH*IMAGE_HEIGHT;n++)
 {
  ThermalImage[n]=0x00;
  ColorImage[n]=0xFF808080;
 }
 for(n=0;n<VIDEO_WIDTH*VIDEO_HEIGHT;n++) VideoImage[n]=0xFF808080;

 cRingBuffer_Ptr=new CRingBuffer(IMAGE_BUFFER_SIZE);

 FrameIndex=0;

 ShowVideo=false;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CFlirOneReceiver::~CFlirOneReceiver()
{
 delete[](ThermalImage);
 delete[](ColorImage);
 delete[](VideoImage);
 delete(cRingBuffer_Ptr);
}
//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//вычислить crc
//----------------------------------------------------------------------------------------------------
void CFlirOneReceiver::CalculateCRC(uint16_t &crc,uint8_t byte)
{
 crc^=(byte<<8);
 for(uint8_t n=0;n<8;n++)
 {
  if (crc&0x8000) crc=(crc<<1)^0x1021;
             else crc<<=1;
 }
}


//****************************************************************************************************
//открытые функции
//****************************************************************************************************
//----------------------------------------------------------------------------------------------------
//создать изображение
//----------------------------------------------------------------------------------------------------
bool CFlirOneReceiver::CreateImage(uint8_t *buffer,uint32_t size)
{
 uint32_t n;
 int32_t x;
 int32_t y;

 //если в принятых данных встретились 4 специальных байта, то начинаем сборку заново
 static uint8_t magic_byte[4]={0xEF,0xBE,0x00,0x00};
 //заполняем буфер
 for(n=0;n<size;n++)
 {
  uint8_t b=buffer[n];
  if (b==magic_byte[MagicPos])
  {
   if (MagicPos==0) MagicHeadPos=cRingBuffer_Ptr->GetHeadPos();
   MagicPos++;
   if (MagicPos==4)
   {
    MagicPos=0;
    HeaderIsReceived=false;
    cRingBuffer_Ptr->SetTailPos(MagicHeadPos);//переносим хвост к голове
   }
  }
  else MagicPos=0;
  cRingBuffer_Ptr->PushByte(b);
 }
 //узнаем, сколько данных в буфере
 uint32_t length=cRingBuffer_Ptr->GetDataSize();
 //прочтем заголовок, так, чтобы не повредить данные в буфере
 if (length<sizeof(SHeader)) return(false);//заголовок не собран
 if (HeaderIsReceived==false)//собираем заголовок
 {
  uint8_t *sheader_ptr=(uint8_t*)(&sHeader);
  uint32_t tail=cRingBuffer_Ptr->GetTailPos();
  for(n=0;n<sizeof(SHeader);n++,sheader_ptr++)
  {
   if (cRingBuffer_Ptr->GetHeadPos()==tail) return(false);//данных почему-то не хватило
   *sheader_ptr=cRingBuffer_Ptr->GetByte(tail);
   tail++;
   if (tail==cRingBuffer_Ptr->GetBufferSize()) tail=0;
  }
  if (sHeader.MagicByte[0]!=magic_byte[0]) return(false);
  if (sHeader.MagicByte[1]!=magic_byte[1]) return(false);
  if (sHeader.MagicByte[2]!=magic_byte[2]) return(false);
  if (sHeader.MagicByte[3]!=magic_byte[3]) return(false);
  HeaderIsReceived=true;
 }
 if (sHeader.FrameSize+sizeof(SHeader)>length) return(false);//кадр ещё не собран
 //кадр собран, считываем заголовок кадра
 uint8_t b;
 for(n=0;n<sizeof(SHeader);n++) cRingBuffer_Ptr->PopByte(&b);
 //кадр собран
 for(n=0;n<IMAGE_WIDTH*IMAGE_HEIGHT;n++)
 {
  ThermalImage[n]=0x00;
  ColorImage[n]=0xFF808080;
 }
 for(n=0;n<VIDEO_WIDTH*VIDEO_HEIGHT;n++) VideoImage[n]=0xFF808080;
 JPGImage.clear();
 //создаём тепловое изображение (164 числа в строке)
 int32_t min=0x10000;
 int32_t max=0x0;
 bool enabled=true;
 for(y=0;y<ORIGINAL_IMAGE_HEIGHT;y++)
 {
  uint16_t crc=0;
  uint16_t id;
  uint16_t crc_package;
  //читаем заголовок
  cRingBuffer_Ptr->PopShort(&id);
  id&=0x0FFF;
  CalculateCRC(crc,(id>>8)&0xFF);
  CalculateCRC(crc,id&0xFF);

  cRingBuffer_Ptr->PopShort(&crc_package);
  CalculateCRC(crc,0);
  CalculateCRC(crc,0);

  for(x=0;x<ORIGINAL_IMAGE_WIDTH/2;x++)
  {
   uint16_t value;
   cRingBuffer_Ptr->PopShort(&value);
   //считаем CRC
   CalculateCRC(crc,*((uint8_t*)(&value)+1));
   CalculateCRC(crc,*((uint8_t*)(&value)));

   uint32_t offset=y+(ORIGINAL_IMAGE_WIDTH-1-x)*ORIGINAL_IMAGE_HEIGHT;
   ThermalImage[offset]=value;
   if (value<min) min=value;
   if (value>max) max=value;
  }
  if (crc!=crc_package)//CRC не совпало
  {
   enabled=false;
   break;
  }

  crc=0;
  //читаем заголовок
  cRingBuffer_Ptr->PopShort(&id);
  id&=0x0FFF;
  CalculateCRC(crc,(id>>8)&0xFF);
  CalculateCRC(crc,id&0xFF);

  cRingBuffer_Ptr->PopShort(&crc_package);
  CalculateCRC(crc,0);
  CalculateCRC(crc,0);

  for(x=ORIGINAL_IMAGE_WIDTH/2;x<ORIGINAL_IMAGE_WIDTH;x++)
  {
   uint16_t value;
   cRingBuffer_Ptr->PopShort(&value);
   //считаем CRC
   CalculateCRC(crc,*((uint8_t*)(&value)+1));
   CalculateCRC(crc,*((uint8_t*)(&value)));
   uint32_t offset=y+(ORIGINAL_IMAGE_WIDTH-1-x)*ORIGINAL_IMAGE_HEIGHT;
   ThermalImage[offset]=value;
   if (value<min) min=value;
   if (value>max) max=value;
  }
  if (crc!=crc_package)//CRC не совпало
  {
   enabled=false;
   break;
  }
 }
 if (enabled==true && ShowVideo==true)
 {
  bool ok=true;
  for(uint32_t n=ORIGINAL_IMAGE_HEIGHT*(ORIGINAL_IMAGE_WIDTH+4)*2;n<sHeader.ThermalSize;n++)
  {
   uint8_t b;
   if (cRingBuffer_Ptr->PopByte(&b)==false)
   {
    ok=false;
    break;
   }
  }
  if (ok==true)
  {
   JPGImage.reserve(sHeader.JpgSize);

   for(uint32_t n=0;n<sHeader.JpgSize;n++)
   {
    uint8_t b;
    if (cRingBuffer_Ptr->PopByte(&b)==false)
    {
     JPGImage.clear();
     ok=false;
     break;
    }
    JPGImage.push_back(b);
   }
   if (ok==true)
   {
    unsigned long jpg_size=sHeader.JpgSize;
    unsigned char *jpg_buffer=&JPGImage[0];
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    int row_stride, width, height, pixel_size;
    cinfo.err=jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_mem_src(&cinfo,jpg_buffer,jpg_size);
    int rc=jpeg_read_header(&cinfo,TRUE);
    if (rc==1)//данные являются нормальным jpeg-изображением
    {
     jpeg_start_decompress(&cinfo);
     width=cinfo.output_width;
     height=cinfo.output_height;
     pixel_size=cinfo.output_components;
     row_stride=width*pixel_size;
     int bmp_size=width*height*pixel_size;
     unsigned char *bmp_buffer=new unsigned char[bmp_size];
     //читаем изображение
     while (cinfo.output_scanline < cinfo.output_height)
     {
      unsigned char *buffer_array[1];
      buffer_array[0]=bmp_buffer+(cinfo.output_scanline)*row_stride;
      jpeg_read_scanlines(&cinfo,buffer_array,1);
     }
     jpeg_finish_decompress(&cinfo);
     jpeg_destroy_decompress(&cinfo);
     //переносим изображение из буфера
     for(int32_t x=0;x<width;x++)
     {
      for(int32_t y=0;y<height;y++)
      {
       uint32_t bmp_offset=(x+y*width)*3;
       uint32_t offset=(width-1-x)*ORIGINAL_VIDEO_HEIGHT+y;
       uint32_t r=bmp_buffer[bmp_offset+0];
       uint32_t g=bmp_buffer[bmp_offset+1];
       uint32_t b=bmp_buffer[bmp_offset+2];
       VideoImage[offset]=b|(g<<8)|(r<<16)|(0xFF<<24);
      }
     }
     delete[](bmp_buffer);
    }
   }
 /*
   //сохраняем jpg-картинку, для чего создаём поток
   IStream *pStream=NULL;
   if (SUCCEEDED(CreateStreamOnHGlobal(NULL,true,&pStream)))
   {
    for(uint32_t n=0;n<sHeader.JpgSize;n++)
    {
     uint8_t b;
     if (cRingBuffer_Ptr->PopByte(&b)==false)
     {
      JPGImage.clear();
      ok=false;
      break;
     }
     pStream->Write(&b,1,0);//записываем в поток наши данные
     JPGImage.push_back(b);
    }
    if (ok==true)
    {
     //создаём изображение
     Bitmap bitmap(pStream,0);
     //копируем данные изображения в массив
     int32_t width=bitmap.GetWidth();
     int32_t height=bitmap.GetHeight();
     for(int32_t x=0;x<width;x++)
     {
      for(int32_t y=0;y<height;y++)
      {
       Color color;
       bitmap.GetPixel(x,y,&color);
       uint32_t offset=(width-1-x)*ORIGINAL_VIDEO_HEIGHT+y;
       uint32_t r=color.GetRed();
       uint32_t g=color.GetGreen();
       uint32_t b=color.GetBlue();
       VideoImage[offset]=b|(g<<8)|(r<<16)|(0xFF<<24);
      }
     }
    }
    pStream->Release();    
   }
   */
  }
 }

 cRingBuffer_Ptr->Reset();
 MagicPos=0;
 MagicHeadPos=0;
 HeaderIsReceived=false;

 if (enabled==true)
 {
  //создаём раскрашенное изображение
  int32_t delta=max-min;
  if (delta==0) delta=1;
  for(x=0;x<ORIGINAL_IMAGE_WIDTH;x++)
  {
   for(y=0;y<ORIGINAL_IMAGE_HEIGHT;y++)
   {
    int32_t offset=x+y*ORIGINAL_IMAGE_WIDTH;
    int32_t value=ThermalImage[offset];
    value-=min;
    value=(value*255)/delta;
    offset=x+y*ORIGINAL_IMAGE_WIDTH;
    value&=0xff;
    uint32_t color=0;
    color|=0xff;
    color<<=8;
    color|=ColorMap_R[value];
    color<<=8;
    color|=ColorMap_G[value];
    color<<=8;
    color|=ColorMap_B[value];
    ColorImage[offset]=color;
   }
  }
  FrameIndex++;
  return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//загрузить карту перекодировки изображения
//----------------------------------------------------------------------------------------------------
bool CFlirOneReceiver::LoadColorMap(const std::string &filename)
{
 FILE *file=fopen(filename.c_str(),"rb");
 if (file==NULL) return(false);
 uint8_t colormap[COLOR_MAP_UNIT*COLOR_SIZE];
 if (fread(colormap,sizeof(uint8_t),COLOR_MAP_UNIT*COLOR_SIZE,file)<768)
 {
  fclose(file);
  return(false);
 }
 fclose(file);
 for(int32_t n=0;n<COLOR_MAP_UNIT;n++)
 {
  ColorMap_R[n]=colormap[n*COLOR_SIZE+0];
  ColorMap_G[n]=colormap[n*COLOR_SIZE+1];
  ColorMap_B[n]=colormap[n*COLOR_SIZE+2];
 }
 return(true);
}

//----------------------------------------------------------------------------------------------------
//скопировать раскрашенное изображение в буфер
//----------------------------------------------------------------------------------------------------
bool CFlirOneReceiver::CopyColorImage(uint32_t* image_ptr,uint32_t size,uint32_t &index)
{
 if (size<COLOR_IMAGE_SIZE_LONG) return(false);//буфер слишком мал
 index=FrameIndex;
 memcpy(image_ptr,ColorImage,COLOR_IMAGE_SIZE_LONG*sizeof(uint32_t));
 return(true);
}
//----------------------------------------------------------------------------------------------------
//скопировать тепловое изображение в буфер
//----------------------------------------------------------------------------------------------------
bool CFlirOneReceiver::CopyThermalImage(uint16_t *image_ptr,uint32_t size,uint32_t &index)
{
 if (size<THERMAL_IMAGE_SIZE_SHORT) return(false);//буфер слишком мал
 index=FrameIndex;
 memcpy(image_ptr,ThermalImage,THERMAL_IMAGE_SIZE_SHORT*sizeof(uint16_t));
 return(true);
}
//----------------------------------------------------------------------------------------------------
//скопировать изображение с видеокамеры в буфер
//----------------------------------------------------------------------------------------------------
bool CFlirOneReceiver::CopyVideoImage(uint32_t *image_ptr,uint32_t size,uint32_t &index)
{
 if (ShowVideo==false) return(false);
 if (size<VIDEO_IMAGE_SIZE_LONG) return(false);//буфер слишком мал
 index=FrameIndex;
 memcpy(image_ptr,VideoImage,VIDEO_IMAGE_SIZE_LONG*sizeof(uint32_t));
 return(true);
}
//----------------------------------------------------------------------------------------------------
//скопировать данные с видеокамеры в буфер
//----------------------------------------------------------------------------------------------------
bool CFlirOneReceiver::CopyJPGImage(std::vector<uint8_t> &vector_jpg,uint32_t &index)
{
 if (ShowVideo==false) return(false);
 vector_jpg=JPGImage;
 index=FrameIndex;
 return(true);
}
//---------------------------------------------------------------------------
//скопировать палитру
//---------------------------------------------------------------------------
bool CFlirOneReceiver::CopyColorMap(uint8_t R[256],uint8_t G[256],uint8_t B[256],uint32_t size)
{
 if (size<COLOR_MAP_UNIT) return(false);//буфер слишком мал
 for(int32_t n=0;n<COLOR_MAP_UNIT;n++)
 {
  R[n]=ColorMap_R[n];
  G[n]=ColorMap_G[n];
  B[n]=ColorMap_B[n];
 }
 return(true);
}
//---------------------------------------------------------------------------
//показывать ли видео
//---------------------------------------------------------------------------
void CFlirOneReceiver::SetShowVideo(bool state)
{
 ShowVideo=state;
}
