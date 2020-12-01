#ifndef __INTERPRT__H__
#define __INTERPRT__H__

#include "units.h"
#include "initialization.h"
#include "processing.h"

// поиск переменной по названию 
int findVarFromName(std::string varName, _variables varList);

// интерпритация инициализация переменной
void varInitInterpretation(std::string source, WPTool::string_vect types, _variables &varList); 

// проверка на ошибки в инициализации 
void varInitErr(_variable var, _variables &varList);

// итерпритация инициализации переменной типа num
void numVarInitIterpr(_variable &var, _variables &varList);

// интерпритация обьявления функции 
void funcInitInterpretation(std::string source, WPTool::string_vect types, _functions &funcList);

// получение результата функции
std::string getFuncResult(std::string source, _functions &funcList);

#endif 