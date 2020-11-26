#include "units.h"

bool conformity_to_all_types(std::string type,  std::vector<std::string> types){
    for(std::size_t i = 0; i < types.size(); i++){
        if(type == types[i]){
            return true;
        }
    }
    return false;
}

_variable::_variable(_baseCodeUnit copy){
    this->name = copy.name;
    this->type = copy.type;
}

_function::_function(_baseCodeUnit copy){
    this->name = copy.name;
    this->type = copy.type;
}