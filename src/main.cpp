#include "initialization.h"
#include <iostream>


void varInitErr(_variable var, _variables & varList){
    for(_variables::iterator _varIT = varList.begin(); _varIT != varList.end(); ++_varIT){
        if(_varIT->name == var.name ){
            throw "same variable names";
        }
    }
}

void varInitInterpretation(std::string source, WPTool::string_vect types, _variables &varList){
    try{ 
        _variable var(initVariable(source));
        varInitErr(var,varList);
        if(!conformity_to_all_types(var.type,types)){
            throw "error var type";
        }
        varList.push_back(var);   
    }
    catch(const char * _error_message){
        printf("%s\n", _error_message);
    }
}

_variables vars;

WPTool::string_vect _types {  // типы данных 
    "file", "folder", "str", "num", "proc"
};   

int main(){
    varInitInterpretation("list[num] a = { 1, 2, 3, 4}",_types , vars);
    varInitInterpretation("list[num] a = { 1, 2, 3, 4}",_types , vars);
    _variable var = vars[0];
    std::cout << var.name << std::endl;
    std::cout << var.properties["object0"] << std::endl;
    std::cout << var.properties["object1"] << std::endl;
    std::cout << var.properties["object2"] << std::endl;
    std::cout << var.type << std::endl;
    return 0;
}