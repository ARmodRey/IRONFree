#include "processing.h"

_action getActionType(std::string codeLIne, WPTool::string_vect _types){
    WPTool::string_content line(codeLIne," \t");    
    if(conformity_to_all_types(line[0],_types)){
        return is_init;
    }
    line.set_delimetr(" \t(){}");
    if(line[0] == "use"){
        return is_use;
    }
    else{
        return is_empl;
    } 
}