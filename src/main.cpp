#include "interpreter.h"
#include <iostream>

int main(){
    _variable var = getVariable("list lst[file] { one, two }");
    std::cout << var.name << std::endl;
    std::cout << var.object[0] << std::endl;
    std::cout << var.object[1] << std::endl;
    std::cout << var.type << std::endl;
    return 0;
}