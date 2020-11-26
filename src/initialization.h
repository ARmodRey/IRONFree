#ifndef __DECRPRT__H__
#define __DECRPRT__H__

#include "WPTool.h"
#include "units.h"

// проверяе соответствие c типами
bool conformity_to_all_types(std::string type_name, std::vector<std::string> types); 

// для работы с обьявлением переменных 
std::string getName(std::string code_str);        // получаем имя 
std::string getType(std::string code_str);        // получаем тип
_properties getProperties(std::string code_str);  // получаем свойства
_variable initVariable(std::string code_str);      // работаем с переменной   

// для работы с обьявлением функций

#endif