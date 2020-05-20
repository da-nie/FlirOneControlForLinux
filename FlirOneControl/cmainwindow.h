#ifndef C_MAIN_WINDOW_H
#define C_MAIN_WINDOW_H

//****************************************************************************************************
//Класс главного окна программы
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include <QMainWindow>
#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include "iimage.h"
#include "cflironecontrol.h"
#include "clabel_imagearea.h"
#include "cgraphics.h"

//****************************************************************************************************
//пространства имён
//****************************************************************************************************
namespace Ui
{
 class CMainWindow;
}

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//предварительные объявления
//****************************************************************************************************

//****************************************************************************************************
//Класс главного окна программы
//****************************************************************************************************
class CMainWindow:public QMainWindow
{
 Q_OBJECT
 private:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
  static const uint32_t TIMER_INTERVAL_MS=100;//интервал срабатывания таймера, мс
  static const int32_t FRAME_SIZE=3;//размер области измерения температуры
  static const int32_t IMAGE_VIEW_WIDTH=(CFlirOneReceiver::IMAGE_WIDTH+4+CGraphics::FONT_WIDTH*7);
  static const int32_t IMAGE_VIEW_HEIGHT=(CFlirOneReceiver::IMAGE_HEIGHT);
  static const size_t PATH_STRING_BUFFER_SIZE=1024;//размер строки для пути
  static const size_t STRING_BUFFER_SIZE=255;//размер строки

  static const uint32_t COLOR_WHITE=0xFFFFFFFF;//белый цвет
  static const uint32_t COLOR_BLACK=0xFF000000;//чёрный цвет

  static const uint32_t ALARM_MAX_TEMPER_COUNTER_MAX_VALUE=5;//максимальное значение количества кадров с температурой выше маемимума до срабатывания сигнала
  static const uint32_t ALARM_MIN_TEMPER_COUNTER_MAX_VALUE=5;//максимальное значение количества кадров с температурой ниже минимума до срабатывания сигнала
 private:
  //-переменные-----------------------------------------------------------------------------------------
  Ui::CMainWindow *ui;//пользовательский интерфейс
  CFlirOneControl cFlirOneControl;//класс управления тепловизором Flir One
  int32_t TimerId;//идентификатор таймера

  uint32_t AlarmMaxTemperCounter;//счётчик количества кадров с температурой выше максимума до срабатывания сигнала
  uint32_t AlarmMinTemperCounter;//счётчик количества кадров в температурой ниже минимума до срабатывания сигнала

  CLabel_ImageArea *cLabel_ImageArea_ThermalImage_Ptr;//тепловое изображение
  CLabel_ImageArea *cLabel_ImageArea_VideoImage_Ptr;//видео  

  std::vector<uint32_t> ViewImage;//изображение, выводимое на экран
  std::vector<uint32_t> SaveViewImage;//изображение, сохраняемое в файл (если сохранается полная картинка со шкалой)

  std::vector<uint32_t> ColorImage;//раскрашенное изображение
  std::vector<uint16_t> ThermalImage;//тепловое изображение
  std::vector<uint32_t> VideoImage;//изображение с видеокамеры
  std::vector<float> TemperatureImage;//температурное изображение

  uint32_t LastReceivedFrameIndex;//индекс последнего принятого изображения

  CGraphics cGraphics;//класс для рисования на изображении

  std::vector<std::string> vector_PaletteFileName;//список палитр

  IImage *iImage_VideoPtr;//выводимый на экран кадр изображения с видеокамеры
  IImage *iImage_ViewPtr;//выводимое на экран изображение

  //параметры для расчёта температуры
  double PlanckR1;
  double PlanckB;
  double PlanckF;
  double PlanckO;
  double PlanckR2;

  double TempReflected;//температура болометров
  double Emissivity;//коэффициент излучения

  bool SaveAllFrame;//сохранять ли все кадры
  bool SaveImageNoScale;//сохранять без шкалы
  bool SaveImageCross;//рисовать перекрестье
  bool SaveRAW;//сохранять RAW
  bool SaveVideo;//сохранять картинку с видеокамеры
  bool ShowVideo;//показывать видео

 public:
  //-конструктор----------------------------------------------------------------------------------------
  explicit CMainWindow(QWidget *parent=0);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CMainWindow();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
  void timerEvent(QTimerEvent *qTimerEvent_Ptr);//обработчик таймера
  void NewFrame(void);//новый кадр
  bool MinTemperControl(float t);//контроль минимальной температуры
  bool MaxTemperControl(float t);//контроль максимальной температуры
  void FindPalette(void);//поиск палитр
  void ChangeState(bool &state,QWidget *qWidget_Ptr);//смена состояния кнопки и значения флага
  void SetState(bool &state,QWidget *qWidget_Ptr,bool set_state);//задать состояние кнопки и флага
  bool GetTemperature(uint16_t raw14,double &value);//вычислить температуру
  void SaveThermalImage(void);//сохранить тепловое изображение
  void SaveColorImage(void);//сохранить раскрашенное изображение
  void SaveVideoImage(void);//сохранить кадр с видеокамеры
  void ApplyLanguage(void);//применить выбранный язык
 private slots:
  //-закрытые слоты-------------------------------------------------------------------------------------
  void on_pushButton_ApplyPalette_clicked();//нажата кнопка "Применить палитру"
  void on_pushButton_SaveVideo_clicked();//нажата кнопка "Сохранять кадры с видеокамеры"
  void on_pushButton_SaveImageCross_clicked();//нажата кнопка "Рисовать перекрестье"
  void on_pushButton_SaveImageNoScale_clicked();//нажата кнопка "Сохранять изображение без шкалы"
  void on_pushButton_SaveRAW_clicked();//нажата кнопка "Сохранять файл RAW"
  void on_pushButton_ShowVideo_clicked();//нажата кнопка "Показывать видео"
  void on_pushButton_SaveAllFrame_clicked();//нажата кнопка "Сохранять все кадры"
  void on_pushButton_SaveFrame_clicked();//нажата кнопка "Сохранить один кадр"
  void on_comboBox_Language_currentIndexChanged(const QString &arg1);//изменился выбор языкаS
};


#endif
