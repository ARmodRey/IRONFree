#include "processing.h"

_action getActionType(std::string codeLine, WPTool::string_vect _types){
    WPTool::string_content line(codeLine," \t;");    
    if(conformity_to_all_types(line[0],_types) || line.get_size() >= 2){
        return is_init; // инициализация  
    }
    line.set_delimetr(" \t(){}");
    if(line[0] == "use"){
        return is_use; // использование внешних элементов
    }
    else{
        return is_empl; // использоване переменных или функций
    } 
}

_init getInitType(std::string codeLine){
    WPTool::string_content line(codeLine," \t;");
    if(!line.have("=")){
        line.set_string(line[1]);
        if(!line.have("(") && !line.have(")")){
            return _var;
        }
        return _func;
    }
    else{
        return _var;
    }
}

_empl getEmplType(std::string codeLine){
    WPTool::string_content line(codeLine," \t;");
    if(line.have("=")){
        return _use_var;
    }
    if(line.have("(") && line.have("(") && !line.have("=")){
        return _use_func;
    }
    if(line.have("if")){
        return _c_if;
    }
    if(line.have("for")){
        return _c_for;
    }
    if(line.have("while")){
        return _c_wh;
    }
}