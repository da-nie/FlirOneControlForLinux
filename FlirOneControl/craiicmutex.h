#ifndef C_RAII_CMUTEX_H
#define C_RAII_CMUTEX_H

//****************************************************************************************************
//описание
//****************************************************************************************************

//Класс RAII для работы с мютексом

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include "cmutex.h"

//****************************************************************************************************
//класс RAII критической секции
//****************************************************************************************************
class CRAIICMutex
{
 private:
  CMutex *cMutex_Ptr;//указатель на мютекс
  bool Locked;//состояние мютекса
 public:
  CRAIICMutex(CMutex *cMutex_Set_Ptr)//конструктор
  {
   Locked=false;
   if (cMutex_Set_Ptr==NULL) return;
   cMutex_Ptr=cMutex_Set_Ptr;

   Lock();
  }
  ~CRAIICMutex()
  {
   if (cMutex_Ptr==NULL) return;
   Unlock();
  }
  void Lock(void)
  {
   if (cMutex_Ptr==NULL) return;
   if (Locked==true) return;
   cMutex_Ptr->Lock();
   Locked=true;
  }
  void Unlock(void)
  {
   if (cMutex_Ptr==NULL) return;
   if (Locked==false) return;
   cMutex_Ptr->Unlock();
   Locked=false;
  }
};

#endif
