#ifndef __UNITS__H__
#define __UNITS__H__

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::string> _properties;

struct _baseCodeUnit{
    std::string name;
    std::string type;
};

struct _variable : _baseCodeUnit{
    _properties properties;  // значения
};

struct _function : _baseCodeUnit{
    std::vector<_variable> params;        // параметры
    std::vector<std::string> description; // описание
};

struct _instruction : _baseCodeUnit{
    std::vector<_variable> variables;
};

struct _codePart{
    std::vector<_variable> variables;
    std::vector<_instruction> instructions;
    std::vector<_baseCodeUnit*> inter_quene;
};

#endif