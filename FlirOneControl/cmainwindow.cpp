//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "cpicture.h"
#include "cdecorator_scale.h"
#include "system.h"
#include <vector>

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
CMainWindow::CMainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::CMainWindow)
{
 ui->setupUi(this);
 setWindowTitle(tr("Работы с тепловизором flir One"));
 cLabel_ImageArea_ThermalImage_Ptr=new CLabel_ImageArea(IMAGE_VIEW_WIDTH,IMAGE_VIEW_HEIGHT,ui->CLabel_ThermalImage);
 cLabel_ImageArea_VideoImage_Ptr=new CLabel_ImageArea(CFlirOneReceiver::VIDEO_WIDTH,CFlirOneReceiver::VIDEO_HEIGHT,ui->CLabel_VideoImage);

 ViewImage.resize(IMAGE_VIEW_WIDTH*IMAGE_VIEW_HEIGHT,0);
 SaveViewImage.resize(IMAGE_VIEW_WIDTH*IMAGE_VIEW_HEIGHT,0);
 ColorImage.resize(CFlirOneReceiver::IMAGE_WIDTH*CFlirOneReceiver::IMAGE_HEIGHT,0);
 VideoImage.resize(CFlirOneReceiver::VIDEO_WIDTH*CFlirOneReceiver::VIDEO_HEIGHT,0);
 ThermalImage.resize(CFlirOneReceiver::IMAGE_WIDTH*CFlirOneReceiver::IMAGE_HEIGHT,0);

 TemperatureImage.resize(CFlirOneReceiver::IMAGE_WIDTH*CFlirOneReceiver::IMAGE_HEIGHT,0);
 cGraphics.Init(&ViewImage[0],IMAGE_VIEW_WIDTH,IMAGE_VIEW_HEIGHT);

 LastReceivedFrameIndex=0;

 iImage_VideoPtr=new CPicture;
 iImage_VideoPtr->SetSize(CFlirOneReceiver::VIDEO_WIDTH,CFlirOneReceiver::VIDEO_HEIGHT);
 iImage_VideoPtr=new CDecorator_Scale(iImage_VideoPtr,CFlirOneReceiver::VIDEO_WIDTH,CFlirOneReceiver::VIDEO_HEIGHT);

 iImage_ViewPtr=new CPicture;
 iImage_ViewPtr->SetSize(IMAGE_VIEW_WIDTH,IMAGE_VIEW_HEIGHT);
 iImage_ViewPtr=new CDecorator_Scale(iImage_ViewPtr,IMAGE_VIEW_WIDTH,IMAGE_VIEW_HEIGHT);

 cFlirOneControl.LoadColorMap("./Palette/iron.pal");//загружаем палитру

 PlanckR1=16528.178;
 PlanckB=1427.5;
 PlanckF=1.0;
 PlanckO=-1307.0;
 PlanckR2=0.012258549;

 TempReflected=20;
 Emissivity=0.95;

 SaveAllFrame=false;
 SaveImageNoScale=false;
 SaveImageCross=false;
 SaveRAW=false;
 SaveVideo=false;
 ShowVideo=false;

// cFlirOneControl.SetShowVideo(false);
 cFlirOneControl.SetShowVideo(true);

 //подключим таймер обновления экрана
 TimerId=startTimer(TIMER_INTERVAL_MS);
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CMainWindow::~CMainWindow()
{ 
 delete(iImage_VideoPtr);
 delete(iImage_ViewPtr);
 killTimer(TimerId);
 delete(ui);
}


//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//обработчик таймера
//----------------------------------------------------------------------------------------------------
void CMainWindow::timerEvent(QTimerEvent *qTimerEvent_Ptr)
{
 static const float T_MAX_INITIAL_VALUE=-10000;//начальное значение для максимальной температуры
 static const float T_MIN_INITIAL_VALUE=10000;//начальное значение для минимальной температуры
 static const float T_MIN_VALID_VALUE=-999;//минимальное допустимое значение температуры
 static const float T_MAX_VALID_VALUE=999;//максимальное допустимое значение температуры
 static const int32_t MAX_COLOR_INDEX=CFlirOneReceiver::COLOR_MAP_UNIT-1;//максимальный индекс цвета в палитре

 if (qTimerEvent_Ptr->timerId()!=TimerId) return;
 int32_t x;
 int32_t y;
 //считываем температуру болометров и коэффициент излучения
 //char string[255];
 //((CEdit *)GetDlgItem(IDC_EDIT_MAIN_TEMPERATURE))->GetWindowText(string,255);
 TempReflected=20;//atof(string);
 //((CEdit *)GetDlgItem(IDC_EDIT_MAIN_EMISSION))->GetWindowText(string,255);
 Emissivity=0.98;//atof(string);
 //копируем изображение
 uint32_t index;
 //получаем тепловое изображение
 cFlirOneControl.CopyThermalImage(&ThermalImage[0],CFlirOneReceiver::THERMAL_IMAGE_SIZE_SHORT,index);
 //получаем раскрашенное изображение
 cFlirOneControl.CopyColorImage(&ColorImage[0],CFlirOneReceiver::COLOR_IMAGE_SIZE_LONG,index);
 //получаем видео изображение
 cFlirOneControl.CopyVideoImage(&VideoImage[0],CFlirOneReceiver::VIDEO_IMAGE_SIZE_LONG,index);
 if (LastReceivedFrameIndex!=index)//изображение изменилось
 {
  //копируем кадр видео
  iImage_VideoPtr->SetRGBAImage(CFlirOneReceiver::VIDEO_WIDTH,CFlirOneReceiver::VIDEO_HEIGHT,VideoImage);
  //копируем изображение
  uint32_t *v1_ptr=&ViewImage[0];
  uint32_t *v2_ptr=&ColorImage[0];
  for(y=0;y<CFlirOneReceiver::IMAGE_HEIGHT;y++,v1_ptr+=IMAGE_VIEW_WIDTH,v2_ptr+=CFlirOneReceiver::IMAGE_WIDTH)
  {
   uint32_t *v1_ptr_local=v1_ptr;
   uint32_t *v2_ptr_local=v2_ptr;
   for(x=0;x<CFlirOneReceiver::IMAGE_WIDTH;x++,v1_ptr_local++,v2_ptr_local++) *v1_ptr_local=*v2_ptr_local;
  }
  //очищаем места для максимальной и минимальной температуры
  cGraphics.SolidFill(CFlirOneReceiver::IMAGE_WIDTH+2,CFlirOneReceiver::IMAGE_HEIGHT-CGraphics::FONT_HEIGHT*2-2-4,IMAGE_VIEW_WIDTH-(CFlirOneReceiver::IMAGE_WIDTH+2),CGraphics::FONT_HEIGHT*2+4,0);
  cGraphics.SolidFill(CFlirOneReceiver::IMAGE_WIDTH+2,2,IMAGE_VIEW_WIDTH-(CFlirOneReceiver::IMAGE_WIDTH+2),CGraphics::FONT_HEIGHT,0);
  //рисуем градиентную шкалу
  uint32_t scale_height=IMAGE_VIEW_HEIGHT-8-CGraphics::FONT_HEIGHT*3-4;
  float c_index=MAX_COLOR_INDEX;
  float dc_index=static_cast<float>(MAX_COLOR_INDEX)/static_cast<float>(scale_height);
  v1_ptr=&ViewImage[0]+(4+CGraphics::FONT_HEIGHT)*IMAGE_VIEW_WIDTH+CFlirOneReceiver::IMAGE_WIDTH+2;
  uint8_t R[CFlirOneReceiver::COLOR_MAP_UNIT];
  uint8_t G[CFlirOneReceiver::COLOR_MAP_UNIT];
  uint8_t B[CFlirOneReceiver::COLOR_MAP_UNIT];
  cFlirOneControl.CopyColorMap(R,G,B,CFlirOneReceiver::COLOR_MAP_UNIT);
  for(y=0;y<scale_height;y++,v1_ptr+=IMAGE_VIEW_WIDTH,c_index-=dc_index)
  {
   uint32_t index=static_cast<uint32_t>(c_index);
   uint32_t color=0;
   color|=0xff;
   color<<=8;
   color|=R[index];
   color<<=8;
   color|=G[index];
   color<<=8;
   color|=B[index];
   uint32_t *v1_ptr_local=v1_ptr;
   for(x=0;x<IMAGE_VIEW_WIDTH-CFlirOneReceiver::IMAGE_WIDTH-4;x++,v1_ptr_local++) *v1_ptr_local=color;
  }
  //считаем температуру по кадру
  char string[STRING_BUFFER_SIZE];
  double t_max=T_MAX_INITIAL_VALUE;
  double t_min=T_MIN_INITIAL_VALUE;
  double t=0;
  long point=0;//количество точек
  uint16_t *t_ptr=&ThermalImage[0];
  float *tmr_ptr=&TemperatureImage[0];
  uint32_t *v_ptr=&ViewImage[0];
  for(y=0;y<CFlirOneReceiver::IMAGE_HEIGHT;y++,v_ptr+=IMAGE_VIEW_WIDTH)
  {
   uint32_t *v_ptr_local=v_ptr;
   for(x=0;x<CFlirOneReceiver::IMAGE_WIDTH;x++,t_ptr++,v_ptr_local++,tmr_ptr++)
   {
    //вычисляем температуру
    double pt;//температура в точке
    *tmr_ptr=T_MAX_INITIAL_VALUE;
    if (GetTemperature(*t_ptr,pt)==false) continue;//ошибка вычисления температуры
    *tmr_ptr=pt;
    if (pt>t_max) t_max=pt;
    if (pt<t_min) t_min=pt;
    if (x>=CFlirOneReceiver::IMAGE_WIDTH/2-FRAME_SIZE && x<=CFlirOneReceiver::IMAGE_WIDTH/2+FRAME_SIZE)
    {
     if (y>=CFlirOneReceiver::IMAGE_HEIGHT/2-FRAME_SIZE && y<=CFlirOneReceiver::IMAGE_HEIGHT/2+FRAME_SIZE)
     {
      point++;
      t+=pt;
     }
    }
   }
  }
  if (point!=0)
  {
   t/=static_cast<double>(point);
   //выводим температуру
   if (t>=T_MIN_VALID_VALUE && t<=T_MAX_VALID_VALUE)
   {
    snprintf(string,STRING_BUFFER_SIZE,"%.1f!",t);
    cGraphics.PutString(CFlirOneReceiver::IMAGE_WIDTH+2,IMAGE_VIEW_HEIGHT-CGraphics::FONT_HEIGHT-2,string,0xFFFFFF);
   }
  }
  //выводим минимальную температуру
  if (t_min>=T_MIN_VALID_VALUE && t_min<=T_MAX_VALID_VALUE)
  {
   snprintf(string,STRING_BUFFER_SIZE,"%.1f!",t_min);
   cGraphics.PutString(CFlirOneReceiver::IMAGE_WIDTH+2,IMAGE_VIEW_HEIGHT-CGraphics::FONT_HEIGHT*2-2-4,string,0xFFFFFF);
  }
  //выводим максимальную температуру
  if (t_max>=T_MIN_VALID_VALUE && t_max<=T_MAX_VALID_VALUE)
  {
   snprintf(string,STRING_BUFFER_SIZE,"%.1f!",t_max);
   cGraphics.PutString(CFlirOneReceiver::IMAGE_WIDTH+2,2,string,0xFFFFFF);
  }
  if (SaveImageCross==false) SaveViewImage=ViewImage;
  //рисуем рамку
  uint32_t *v_ptr_horizontal=&ViewImage[0]+(IMAGE_VIEW_HEIGHT/2-FRAME_SIZE)*IMAGE_VIEW_WIDTH+CFlirOneReceiver::IMAGE_WIDTH/2-FRAME_SIZE;
  uint32_t *v_ptr_vertical=v_ptr_horizontal;
  for(long n=0;n<=FRAME_SIZE*2;n++,v_ptr_horizontal++,v_ptr_vertical+=IMAGE_VIEW_WIDTH)
  {
   *v_ptr_horizontal^=0x00FFFFFF;
   *(v_ptr_horizontal+FRAME_SIZE*2*IMAGE_VIEW_WIDTH)^=0x00FFFFFF;
   if (v_ptr_horizontal==v_ptr_vertical) continue;
   if (v_ptr_horizontal+FRAME_SIZE*2*IMAGE_VIEW_WIDTH==v_ptr_vertical+FRAME_SIZE*2) continue;
   *v_ptr_vertical^=0x00FFFFFF;
   *(v_ptr_vertical+FRAME_SIZE*2)^=0x00FFFFFF;
  }
  if (SaveImageCross==true) SaveViewImage=ViewImage;
  //if (SaveAllFrame==true) OnButton_SaveFrame();//сохраняем кадр
  //копируем изображение
  iImage_ViewPtr->SetRGBAImage(IMAGE_VIEW_WIDTH,IMAGE_VIEW_HEIGHT,ViewImage);
  LastReceivedFrameIndex=index;

  cLabel_ImageArea_ThermalImage_Ptr->Redraw(&ViewImage[0]);
  cLabel_ImageArea_VideoImage_Ptr->Redraw(&VideoImage[0]);
  update();
 }
}

//---------------------------------------------------------------------------
//вычислить температуру
//---------------------------------------------------------------------------
bool CMainWindow::GetTemperature(uint16_t raw14,double &value)
{
 static const double ABS_ZERO=273.15;//абсолютный ноль в градусах Цельсия
 if (raw14>=(1<<14)) return(false);//TODO: Надо уточнить верхний предел
 raw14*=4;
 double zn=(PlanckR2*(exp(PlanckB/(TempReflected+273.15))-PlanckF));
 if (fabs(zn)<EPS) return(false);
 double RAWrefl=PlanckR1/zn-PlanckO;
 double RAWobj=(raw14-(1-Emissivity)*RAWrefl)/Emissivity;
 double lgr=PlanckR1/(PlanckR2*(RAWobj+PlanckO)+PlanckF);
 if (lgr<=EPS) return(false);
 value=PlanckB/log(lgr)-ABS_ZERO;
 return(true);
}

//---------------------------------------------------------------------------
//сохранить раскрашенное изображение
//---------------------------------------------------------------------------
void CMainWindow::SaveColorImage(void)
{
 MakeDirectory("./Image");
 //считываем дату и время
 time_t time_main=time(NULL);
 tm *tm_main=localtime(&time_main);
 //ищем свободный файл
 char filename[PATH_STRING_BUFFER_SIZE];
 for(long index=1;index<1000;index++)
 {
  snprintf(filename,PATH_STRING_BUFFER_SIZE,"./Image\\img[%04i.%02i.%02i %02i_%02i_%02i-%03ld].tga",tm_main->tm_year+1900,tm_main->tm_mon+1,tm_main->tm_mday,tm_main->tm_hour,tm_main->tm_min,tm_main->tm_sec,index);
  FILE *file=fopen(filename,"rb");
  if (file==NULL)//такого файла ещё нет
  {
   if (SaveImageNoScale==false) SaveTGA(filename,IMAGE_VIEW_WIDTH,IMAGE_VIEW_HEIGHT,reinterpret_cast<uint8_t*>(&SaveViewImage[0]));
                           else SaveTGA(filename,CFlirOneReceiver::IMAGE_WIDTH,CFlirOneReceiver::IMAGE_HEIGHT,reinterpret_cast<uint8_t*>(&ColorImage[0]));
   break;
  }
  else fclose(file);
 }
}

//---------------------------------------------------------------------------
//сохранить кадр с видеокамеры
//---------------------------------------------------------------------------
void CMainWindow::SaveVideoImage(void)
{
 static const int32_t MIN_FILE_INDEX=1;//минимальный индекс файла для одинакового имени
 static const int32_t MAX_FILE_INDEX=100;//максимальный индекс файла для одинакового имени

 MakeDirectory("./Image");
 //считываем дату и время
 time_t time_main=time(NULL);
 tm *tm_main=localtime(&time_main);
 //ищем свободный файл
 char filename[PATH_STRING_BUFFER_SIZE];
 for(int32_t index=MIN_FILE_INDEX;index<MAX_FILE_INDEX;index++)
 {
  snprintf(filename,PATH_STRING_BUFFER_SIZE,"./Image\\frame[%04i.%02i.%02i %02i_%02i_%02i-%03ld].tga",tm_main->tm_year+1900,tm_main->tm_mon+1,tm_main->tm_mday,tm_main->tm_hour,tm_main->tm_min,tm_main->tm_sec,index);
  FILE *file=fopen(filename,"rb");
  if (file==NULL)//такого файла ещё нет
  {
   SaveTGA(filename,CFlirOneReceiver::VIDEO_WIDTH,CFlirOneReceiver::VIDEO_HEIGHT,reinterpret_cast<uint8_t*>(&VideoImage[0]));
   break;
  }
  else fclose(file);
 }
}

//---------------------------------------------------------------------------
//сохранить тепловое изображение
//---------------------------------------------------------------------------
void CMainWindow::SaveThermalImage(void)
{
 static const int32_t MIN_FILE_INDEX=1;//минимальный индекс файла для одинакового имени
 static const int32_t MAX_FILE_INDEX=100;//максимальный индекс файла для одинакового имени

 MakeDirectory("./Image");
 //считываем дату и время
 time_t time_main=time(NULL);
 tm *tm_main=localtime(&time_main);
 //ищем свободный файл
 char filename[PATH_STRING_BUFFER_SIZE];
 for(int32_t index=MIN_FILE_INDEX;index<MAX_FILE_INDEX;index++)
 {
  snprintf(filename,PATH_STRING_BUFFER_SIZE,"./Image\\img[%04i.%02i.%02i %02i_%02i_%02i-%03ld].raw",tm_main->tm_year+1900,tm_main->tm_mon+1,tm_main->tm_mday,tm_main->tm_hour,tm_main->tm_min,tm_main->tm_sec,index);
  FILE *file=fopen(filename,"rb");
  if (file==NULL)//такого файла ещё нет
  {
   file=fopen(filename,"wb");
   #pragma pack(1)
   struct SHeader
   {
    uint32_t Width;//ширина
    uint32_t Height;//высота
    //параметры для расчёта температуры
    double PlanckR1;
    double PlanckB;
    double PlanckF;
    double PlanckO;
    double PlanckR2;
    double TempReflected;//температура болометров
    double Emissivity;//коэффициент излучения
   } sHeader;
   #pragma pack()
   sHeader.Width=CFlirOneReceiver::IMAGE_WIDTH;
   sHeader.Height=CFlirOneReceiver::IMAGE_HEIGHT;
   sHeader.PlanckR1=PlanckR1;
   sHeader.PlanckB=PlanckB;
   sHeader.PlanckF=PlanckF;
   sHeader.PlanckO=PlanckO;
   sHeader.PlanckR2=PlanckR2;
   sHeader.TempReflected=TempReflected;
   sHeader.Emissivity=Emissivity;
   fwrite(&sHeader,1,sizeof(SHeader),file);//записываем заголовок
   //записываем данные
   fwrite(&ThermalImage[0],CFlirOneReceiver::THERMAL_IMAGE_SIZE_SHORT,sizeof(uint16_t),file);
   fclose(file);
   break;
  }
  else fclose(file);
 }
}


//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
