#include "units.h"

bool conformity_to_all_types(std::string type,  std::vector<std::string> types){
    for(int i = 0; i < types.size(); i++){
        if(type == types[i]){
            return true;
        }
    }
    return false;
}