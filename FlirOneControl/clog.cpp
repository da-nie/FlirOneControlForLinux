//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "clog.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

std::unique_ptr<CLog> CLog::cLog_Ptr;

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
CLog::CLog(void)
{ 
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CLog::~CLog()
{
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************************************
//статические открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//получить указатель на класс вывода работы программы
//----------------------------------------------------------------------------------------------------
CLog* CLog::GetPtr(void)
{
 if (cLog_Ptr.get()==NULL) cLog_Ptr.reset(new CLog());
 return(cLog_Ptr.get());
}

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//добавить строку в log-файл
//----------------------------------------------------------------------------------------------------
void CLog::AddLog(const std::string &string)
{
 return;
 FILE *file=fopen("log.txt","ab");
 if (file==NULL) return;
 fprintf(file,"%s",string.c_str());
 fclose(file);
}
//----------------------------------------------------------------------------------------------------
//добавить число в log-файл
//----------------------------------------------------------------------------------------------------
void CLog::AddLog(int32_t value)
{
 return;
 FILE *file=fopen("log.txt","ab");
 if (file==NULL) return;
 fprintf(file,"%i",value);
 fclose(file);
}

