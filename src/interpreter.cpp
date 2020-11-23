#include "interpreter.h"

bool conformity_to_basic_types(std::string type){
    std::string basic_data_types[5]{ "file" , "folder" , "str", "num", "list" };
    for(int i = 0; i < 5; i++){
        if(type == basic_data_types[i]){
            return true;
        }
    }
    return false;
}

_variable getVariable(std::string code_str){
    _variable result;
    WPTool::string_content str(code_str, " \t[]\"\n;");
    if(conformity_to_basic_types(str[0])){
        if(str[2] == "=>" || str[2] == "="){
            int * start_pos = new int(code_str.find_first_of("\""));
            int * end_pos = new int(code_str.find_last_of("\""));
            if(*start_pos == *end_pos){
                delete start_pos;
                delete end_pos;
                throw "error of name!";
            }
            else{
                result.name = str[1];
                result.type = str[0];
                result.object.push_back(code_str.substr(*start_pos + 1, *end_pos - *start_pos - 1));
            }
            delete start_pos;
            delete end_pos;
        } 
        if(conformity_to_basic_types(str[2])){
            int * start_pos = new int(code_str.find_first_of("{"));
            int * end_pos = new int(code_str.find_last_of("}"));
            if(*start_pos == *end_pos + 1){
                delete start_pos;
                delete end_pos;
            }
            else{
                result.name = str[1];
                result.type = str[0] + "-" + str[2];
                str.set_string(code_str.substr(*start_pos + 1, *end_pos - *start_pos - 1));
                str.set_delimetr(",\t ");
                for(int i = 0; i < str.get_size(); i++){
                    result.object.push_back(str[i]);
                }
            }
            delete start_pos;
            delete end_pos;
        }
    }
    else{
        throw "sinax error!";
    }
    return result;
}