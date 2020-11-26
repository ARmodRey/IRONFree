#include "initialization.h"

bool conformity_to_all_types(std::string type,  std::vector<std::string> types){
    for(int i = 0; i < types.size(); i++){
        if(type == types[i]){
            return true;
        }
    }
    return false;
}

std::string getType(std::string code_str){
    WPTool::string_content str(code_str," \t[]");
    if(str.get_size() == 0){
        throw "Invalid variable declaration";
    }
    if(str[0] == "list" && str.get_size() >= 3){
        return "list[" + str[1] + "]";
    }
    return str[0];
}

std::string getName(std::string code_str){
    WPTool::string_content str(code_str," \t[]");
    if(str[0] == "list" && str.get_size() >= 3){
        return str[2];
    }
    return str[1];
}

_properties getProperties(std::string code_str){
    _properties result;
    int * found = new int(code_str.find_first_of("="));
    if(*found != std::string::npos){
        std::string * prop_string = new std::string(code_str.substr(*found + 1));
        WPTool::string_content str(*prop_string, "\",{} ");
        if(str.get_size() >= 1){
            std::string * count_obj = new std::string;
            for (int i = 0; i < str.get_size(); i++){
                *count_obj = "object" + std::to_string(i);
                result.insert(std::make_pair(*count_obj,str[i]));
            }
            delete count_obj;
        }        
    }
    delete found;
    return result;
}

_variable initVariable(std::string code_str){
    _variable result;
    result.type = getType(code_str);
    result.name = getName(code_str);
    result.properties = getProperties(code_str);
    return result;
}