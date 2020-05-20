//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "clanguageenglish.h"

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
CLanguageEnglish::CLanguageEnglish(void)
{ 
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CLanguageEnglish::~CLanguageEnglish()
{
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

std::string CLanguageEnglish::WindowTitle(void)
{
 return("Flir One control programm");
}
std::string CLanguageEnglish::Label_Emission(void)
{
 return("Emission");
}
std::string CLanguageEnglish::Label_Temper(void)
{
 return("Bolometer temperature");
}
std::string CLanguageEnglish::Label_Palette(void)
{
 return("Palette");
}
std::string CLanguageEnglish::Label_Alarm(void)
{
 return("If the temperature is out of range do:");
}
std::string CLanguageEnglish::Button_ApplyPalette(void)
{
 return("Apply palette");
}
std::string CLanguageEnglish::Button_ShowVideo(void)
{
 return("Show video");
}
std::string CLanguageEnglish::Button_SaveImageCross(void)
{
 return("Save image with cross");
}
std::string CLanguageEnglish::Button_SaveImageNoScale(void)
{
 return("Save image without scale");
}
std::string CLanguageEnglish::Button_SaveRAW(void)
{
 return("Save RAW file");
}
std::string CLanguageEnglish::Button_SaveVideo(void)
{
 return("Save video frame");
}
std::string CLanguageEnglish::Button_SaveAllFrame(void)
{
 return("Save all frame");
}
std::string CLanguageEnglish::Button_SaveFrame(void)
{
 return("Save one frame");
}
std::string CLanguageEnglish::Label_LevelMinT(void)
{
 return("Alarm level min temperature");
}
std::string CLanguageEnglish::Label_LevelMaxT(void)
{
 return("Alarm level max temperature");
}
std::string CLanguageEnglish::CheckBox_SaveFrame(void)
{
 return("Save frame");
}

