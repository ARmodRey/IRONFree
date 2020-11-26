#include "initialization.h"

std::string getType(std::string code_str){
    WPTool::string_content str(code_str," \t[]()");
    if(str.get_size() == 0){
        throw "Invalid variable declaration";
    }
    if(str[0] == "list" && str.get_size() >= 3){
        return "list[" + str[1] + "]";
    }
    return str[0];
}

std::string getName(std::string code_str){
    WPTool::string_content str(code_str," \t[]()");
    if(str[0] == "list" && str.get_size() >= 3){
        return str[2];
    }
    return str[1];
}

_properties getProperties(std::string code_str){
    _properties result;
    std::size_t * found = new std::size_t(code_str.find_first_of("="));
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

bool regularityFuncParameters(_function func){
    if(func.params.size() > 1){
        for(std::size_t i = 1; i < func.params.size(); i++){
            if(!func.params[i-1].properties.empty() && func.params[i].properties.empty()){
                return false;
            }
        }  
    }
    return true;
}

_variables getFuncParameters(std::string code_str){
    _variables result;
    std::size_t * start_pos; 
    std::size_t * end_pos;
    start_pos = new std::size_t(code_str.find("("));
    end_pos = new std::size_t(code_str.find(")"));
    if((*start_pos != *end_pos) && (*start_pos & *end_pos) != std::string::npos){
        std::string params_str = code_str.substr(*start_pos + 1, (*end_pos - *start_pos) - 1);
        WPTool::string_content str(params_str,",");
        if(str.get_size() > 0){
            for(int i = 0; i < str.get_size(); i++){
                _variable param = initVariable(str[i]);
                result.push_back(param);
            } 
        }            
    }
    delete start_pos;
    delete end_pos;
    return result;
}

_function initFunction(std::string code_str){
    _function result;
    result.type = getType(code_str);
    result.name = getName(code_str);
    result.params = getFuncParameters(code_str);
    if(!regularityFuncParameters(result)){
        throw "wrong order of default parameters";
    }
    for(std::size_t i = 0; i < result.params.size(); i++ ){
        if(result.params[i].properties.empty()){
            result.min_count_of_parametrs++;
        }
    }
    return result;
}