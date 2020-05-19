//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cflironedriver.h"
#include "clog.h"

#include <stdio.h>
#include <string.h>


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
CFlirOneDriver::CFlirOneDriver(void)
{ 
 USBDeviceHandle=NULL;
 Ready=false;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CFlirOneDriver::~CFlirOneDriver()
{
 Close();
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//инициализация Flir One
//----------------------------------------------------------------------------------------------------
bool CFlirOneDriver::InitFlirOne(void)
{     
 uint8_t data[2]={0,0};
 //останавливаем интерфейс 2 (FRAME)
 if (libusb_control_transfer(USBDeviceHandle,1,0x0b,0,2,data,0,100)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка остановки интерфейса 2!\r\n");
  return(false);//ошибка настройки
 }
 data[0]=0;
 data[1]=0;
 //останавливаем интерфейс 1 (FILEIO)
 if (libusb_control_transfer(USBDeviceHandle,1,0x0b,0,1,data,0,100)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка остановки интерфейса 1!\r\n");
  return(false);//ошибка настройки
 }
 data[0]=0;
 data[1]=0;
 //запускаем интерфейс 1 (FILEIO)
 if (libusb_control_transfer(USBDeviceHandle,1,0x0b,1,1,data,0,100)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка включения интерфейса 1!\r\n");
  return(false);//ошибка настройки
 }
 //запускаем интерфейс 2 (FRAME)
 data[0]=0;
 data[1]=0;
 if (libusb_control_transfer(USBDeviceHandle,1,0x0b,1,2,data,0,200)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка настройки передачи интерфейса frame!\r\n");
  return(false);//ошибка настройки
 }
 return(true);
}

//----------------------------------------------------------------------------------------------------
//подключение к Flir One
//----------------------------------------------------------------------------------------------------
bool CFlirOneDriver::ConnectToFlirOne(void)
{
 if (libusb_init(NULL)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Не удалось инициализировать LibUsb!\r\n");
  return(false);
 }
 //ищем Flir One Gen 2
 USBDeviceHandle=libusb_open_device_with_vid_pid(NULL,VENDOR_ID,PRODUCT_ID);
 if (USBDeviceHandle==NULL)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Тепловизор Flir One Gen 2 не найден!\r\n");
  return(false);
 }
 CLog::GetPtr()->AddLog("Тепловизор Flir One Gen 2 найден!\r\n");
 //настраиваем конфигурацию устройства
 if (libusb_set_configuration(USBDeviceHandle,3)<0)
 {
  CLog::GetPtr()->CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка настройки конфигурации устройства!\r\n");
  return(false);
 }
 if (libusb_claim_interface(USBDeviceHandle,0)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка включения интерфейса 0!\r\n");
  return(false);
 }
 if (libusb_claim_interface(USBDeviceHandle,1)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка включения интерфейса 1!\r\n");
  return(false);
 }
 if (libusb_claim_interface(USBDeviceHandle,2)<0)
 {
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка включения интерфейса 2!\r\n");
  return(false);
 }
 CLog::GetPtr()->AddLog("Устройство успешно подключено.\r\n");
 return(true);
}


//****************************************************************************************************
//открытые функции
//****************************************************************************************************


//----------------------------------------------------------------------------------------------------
//чтение данных из устройств
//----------------------------------------------------------------------------------------------------
bool CFlirOneDriver::ReadStream(uint8_t* ptr,uint32_t &size)
{
 if (Ready==false) return(false);
 int readen;
 long ret=libusb_bulk_transfer(USBDeviceHandle,0x85,ptr,size,&readen,100);
 size=readen;
 if (ret<0)
 {
  size=0;
  //printf("Error! %s\r\n",libusb_error_name(ret));
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка приёма данных frame! ");
 }
 static const size_t BUFFER_SIZE=1024;
 static uint8_t buffer[BUFFER_SIZE];
 ret=libusb_bulk_transfer(USBDeviceHandle,0x81,buffer,BUFFER_SIZE,&readen,10);
 ret=libusb_bulk_transfer(USBDeviceHandle,0x83,buffer,BUFFER_SIZE,&readen,10);
 if (strcmp(libusb_error_name(ret),"LIBUSB_ERROR_NO_DEVICE")==0)
 {
  Close();
  CLog::GetPtr()->AddLog("[ОШИБКА] Ошибка LIBUSB_ERROR_NO_DEVICE!\r\n");
  return(false);
 }
 return(true);
}


//----------------------------------------------------------------------------------------------------
//подключиться к устройству
//----------------------------------------------------------------------------------------------------
bool CFlirOneDriver::Open(void)
{
 Close();
 if (ConnectToFlirOne()==false)
 {
  Close();
  return(false);
 }
 if (InitFlirOne()==false)
 {
  Close();
  return(false);
 }
 Ready=true;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//отключиться от устройства
//----------------------------------------------------------------------------------------------------
void CFlirOneDriver::Close(void)
{
 if (USBDeviceHandle!=NULL)
 {
  CLog::GetPtr()->AddLog("Устройство отключено.\r\n");
  libusb_reset_device(USBDeviceHandle);
  libusb_close(USBDeviceHandle);
  libusb_exit(NULL);
 }
 Ready=false;
 USBDeviceHandle=NULL;
}
