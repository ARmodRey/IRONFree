#include "initialization.h"
#include <iostream>

int main(){
    _variable var = initVariable("list[file] lst1 = one, two");
    std::cout << var.name << std::endl;
    std::cout << var.properties["object0"] << std::endl;
    std::cout << var.properties["object1"] << std::endl;
    std::cout << var.properties["object2"] << std::endl;
    std::cout << var.type << std::endl;
    return 0;
}