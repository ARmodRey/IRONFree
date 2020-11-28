#include "units.h"

_variable::_variable(_baseCodeUnit copy){
    this->name = copy.name;
    this->type = copy.type;
}

_function::_function(_baseCodeUnit copy){
    this->name = copy.name;
    this->type = copy.type;
}