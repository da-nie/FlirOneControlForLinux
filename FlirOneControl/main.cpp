//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cmainwindow.h"
#include <QApplication>

//****************************************************************************************************
//главная функция программы
//****************************************************************************************************

int main(int argc, char *argv[])
{
 QApplication qApplication(argc,argv);
 CMainWindow cMainWindow;
 cMainWindow.show();
 return(qApplication.exec());
}
