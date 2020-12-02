#include "initialization.h"
#include "interpretation.h"
#include <iostream>

_variables vars;

WPTool::string_vect _types {  // типы данных 
    "file", "folder", "str", "num", "proc"
};   

int main(){
    varInitInterpretation("num b = 10+10-15",_types , vars);
    varInitInterpretation("num a = b-10",_types , vars);
    _variable var = vars[1];
    std::cout << var.name << std::endl;
    std::cout << var.properties["object0"] << std::endl;
    // std::cout << var.properties["object1"] << std::endl;
    // std::cout << var.properties["object2"] << std::endl;
    std::cout << var.type << std::endl;
    return 0;
}