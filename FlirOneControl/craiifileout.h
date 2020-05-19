#ifndef C_RAII_FILE_OUT_H
#define C_RAII_FILE_OUT_H
//****************************************************************************************************
//класс работы с файлами с использованием концепции RAII
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <stdio.h>
#include <string>
#include <fstream>

//****************************************************************************************************
//класс работы с файлами с использованием концепции RAII
//****************************************************************************************************
class CRAIIFileOut
{
 private:
  std::ofstream File;
  std::string FileName;//имя файла
 public:
  //конструктор
  CRAIIFileOut(void)
  {
  }
  //конструктор
  CRAIIFileOut(const std::string &file_name,std::ios_base::openmode mode):FileName(file_name)
  {
   File.open(file_name.c_str(),mode);   
  }
  //деструктор
  ~CRAIIFileOut(void)
  {
   Close();
  }
  //получить класс файла
  std::ofstream& GetHandle(void)
  {
   return(File);
  }
  //узнать, открыт ли файл
  bool IsOpened(void)
  {
   return(File.is_open());
  }
  //получить имя файла
  std::string& GetFileName(void)
  {
   return(FileName);
  }
  //закрыть файл
  void Close(void)
  {
   FileName="";
   File.close();
  }
  //открыть файл
  void Open(const std::string &file_name,std::ios_base::openmode mode)
  {
   Close();
   FileName=file_name;   
   File.open(file_name.c_str(),mode);
  }
};


#endif
