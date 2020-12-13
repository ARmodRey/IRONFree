#include "initialization.h"
#include "interpretation.h"
#include "script.h"
#include <iostream>

_variables vars;

WPTool::string_vect _types {  // типы данных 
    "file", "folder", "str", "num", "proc"
};   

int main(){
    script scr("1");
    scr.runScript();
    
    // _variable var = scr.get_initVars()[2];
    // std::cout << var.name << std::endl;
    // std::cout << var.properties["object0"] << std::endl;
    // std::cout << var.properties["object1"] << std::endl;
    // std::cout << var.properties["object2"] << std::endl;
    // std::cout << var.type << std::endl;  

    _function _func = scr.get_initFuncs()[1];
    std::cout << _func.name << std::endl;
    std::cout << _func.type << std::endl;  
    std::cout << _func.startPos <<std::endl;
    std::cout << _func.endPos <<std::endl;

    return 0;
}