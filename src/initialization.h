#ifndef __DECRPRT__H__
#define __DECRPRT__H__

#include "WPTool.h"
#include "units.h"

// получаем содержимое между двумя символами 
/* 
    позже переедет в WPTool 
*/ 
std::string getStringBetween(std::string source, char begin, char end = '\0'); 

// функции для получения общих для переменных и функций данных 
_baseCodeUnit getCodeUnit(std::string code_str); // получаем тип данных и имя
std::string getName(std::string code_str); // получаем имя переменной или функции
std::string getType(std::string code_str); // получаем тип переменной или функции

// для работы с обьявлением переменных
_properties getProperties(std::string code_str); // получаем свойства
_variable initVariable(std::string code_str);    // работаем с переменной

// для работы с обьявлением функций
_function initFunction(std::string code_str);       // работаем с функцией
_variables getFuncParameters(std::string code_str); // получаем парамеьры функции
bool regularityFuncParameters(_function func);      // проверка параметров функции

// для работы с циклами 
std::string getEndCondition(std::string code_str); // получаем условие окончания инструкция
std::string getInstructionName(std::string code_str); // получаем имя инструкция

#endif