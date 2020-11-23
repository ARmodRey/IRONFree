#ifndef __INTERPRT__H__
#define __INTERPRT__H__

#include "WPTool.h"


struct _baseCodeUnit{
    std::string name;
};

struct _variable : _baseCodeUnit{
    std::string type;
    std::vector<std::string> object;
};

struct _instruction : _baseCodeUnit{
    std::vector<_baseCodeUnit*> variables;
};

struct _codePart{
    std::vector<_variable> variables;
    std::vector<_instruction> instructions;
    std::vector<_baseCodeUnit*> inter_quene;
};

bool conformity_to_basic_types(std::string type);      // проверяе соответствие с основными типами
_variable getVariable(std::string code_str);      // получаем часть кода
std::string getCodeUnitType(_baseCodeUnit & codeUnit); // получаем тип части кода  
std::string getVarType(std::string _code_with_var);    // получаем тип переменной


#endif __INTERPRT__H__