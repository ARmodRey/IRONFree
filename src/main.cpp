#include "initialization.h"
#include <iostream>

int main(){
    _function func = initFunction("file getLastFile(str maindir , str dir = home)");
    std::cout << func.name << std::endl;
    std::cout << func.params[0].name << std::endl;
    std::cout << func.params[0].type << std::endl;
    std::cout << func.params[0].properties["object0"] << std::endl;
    // std::cout << var.properties["object1"] << std::endl;
    // std::cout << var.properties["object2"] << std::endl;
    std::cout << func.type << std::endl;
    std::cout << func.min_count_of_parametrs << std::endl;
    return 0;
}