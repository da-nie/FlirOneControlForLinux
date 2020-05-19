#ifndef C_DECORATOR__I_IMAGE_H
#define C_DECORATOR__I_IMAGE_H

//****************************************************************************************************
//Декоратор для IImage
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "iimage.h"
#include <stdint.h>
#include <vector>

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
//Декоратор для IImage
//****************************************************************************************************
class CDecorator_IImage:public IImage
{
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
 private:
  //-переменные-----------------------------------------------------------------------------------------
  IImage *iImage_Ptr;
 public:
  //-конструктор----------------------------------------------------------------------------------------
  CDecorator_IImage(IImage *iImage_Set_Ptr);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CDecorator_IImage();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void GetRGBAImage(uint32_t &width,uint32_t &height,std::vector<uint32_t> &vector_image);//получить RGBA изображение
  void SetRGBAImage(const uint32_t &width,const uint32_t &height,const std::vector<uint32_t> &vector_image);//задать RGBA изображение
  void SetSize(uint32_t width,uint32_t height);//задать размер изображения и выделить память
  void SetRGBAPixel(uint32_t x,uint32_t y,uint32_t color);//задать точку
  uint32_t GetRGBAPixel(uint32_t x,uint32_t y);//получить точку
 private:
  //-закрытые функции-----------------------------------------------------------------------------------  
};

#endif