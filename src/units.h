#ifndef __UNITS__H__
#define __UNITS__H__

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::string> _properties;

// проверяе соответствие c типами
bool conformity_to_all_types(std::string type_name, std::vector<std::string> types); 

struct _baseCodeUnit{
    std::string name;
    std::string type;
};

struct _variable : _baseCodeUnit{
    _properties properties;  // значения
};

typedef std::vector<_variable> _variables;

struct _function : _baseCodeUnit{
    _variables params;        // параметры
    int min_count_of_parametrs = 0;
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