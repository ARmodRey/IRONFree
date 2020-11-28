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
    _variable(_baseCodeUnit copy);
    _properties properties;  // значения
};

typedef std::vector<_variable> _variables;

struct _function : _baseCodeUnit{
    _function(_baseCodeUnit copy);
    _variables params;        // параметры
    int min_count_of_parametrs = 0;
    int startPos = 0; // позиция начала 
    int endPos = 0;   // позиция окончания 
};

typedef std::vector<_function> _functions;

struct _instruction {
    std::string name;
    std::string condition;
    int startPos = 0; 
    int endPos = 0;
    bool end = false;     
};

struct _codePart{
    std::vector<_variable> variables;
    std::vector<_instruction> instructions;
    std::vector<_baseCodeUnit*> inter_quene;
};

#endif