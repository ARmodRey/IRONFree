#include "interpretation.h"

int findVarFromName(std::string varName, _variables varList){
    for(_variables::iterator _varIT = varList.begin(); _varIT != varList.end(); ++_varIT){
        if(_varIT->name == varName ){
            return std::distance(varList.begin(), _varIT)-1;
        }
    }
    return -1;
}

void varInitErr(_variable var, _variables & varList){
    if(findVarFromName(var.name,varList)){
        throw "same variable names";
    }
}

void varInitInterpretation(std::string source, WPTool::string_vect types, _variables &varList){
    try{ 
        _variable var(initVariable(source));
        varInitErr(var,varList);
        if(!conformity_to_all_types(var.type,types)){
            throw "error var type";
        }
        if(var.type == "num"){ // инициализация переменной типа num
            numVarInitIterpr(var,varList); // вносим переменную в память и проверяем ее значение 
        }
        varList.push_back(var);   
    }
    catch(const char * _error_message){
        printf("%s\n", _error_message);
    }
}

void numVarInitIterpr(_variable &var, _variables &varList){
    if(var.properties.size() == 1 ){
        if(!WPTool::is_digit(var.properties["object0"])){
            throw var.properties["object0"] +  "--> is not digit"; 
        }
        // else if (getEmplType(var.properties["object0"]) == _use_func){
        //     std::string * temp = new std::string(var.properties["object0"]);
        //     var.properties.erase("object0");
        //     var.properties["object0"] = getFuncResult(*temp);
        // }
        else if(findVarFromName(var.name,varList) != -1 ){
            var = varList[findVarFromName(var.name,varList)];
        }
        else if( var.properties["object0"].find_first_of("+-*/") != std::string::npos){
            WPTool::string_content nums(var.properties["object0"],"+-*/");
            WPTool::string_content chars(var.properties["object0"],"1234567890.,");
            int value = 0;
            for(int i = 0; i < nums.get_size(); i++){
                if (findVarFromName(nums[i],varList) != -1 ){
                    nums.edit(i,varList[findVarFromName(var.name,varList)].properties["object0"]);
                }
                else{
                    throw nums[i] + "--> is not digit, and not is init var"; 
                }
                switch (chars[i][0]){
                case '+':
                    value += std::stof(nums[i].c_str());   
                    break;
                case '-':
                    value -= std::stof(nums[i].c_str());   
                    break;
                case '*':
                    value *= std::stof(nums[i].c_str());   
                    break;
                case '/':
                    value /= std::stof(nums[i].c_str());   
                    break;
                default:
                    throw "unknown character or variable";
                    break;
                }
            }
            var.properties.erase("object0");
            var.properties["object0"] = std::to_string(value);
        }
    }
    else if( var.properties.size() > 1 ){
        throw "wrong number of parameters";
    }
}

void funcInitInterpretation(std::string source, WPTool::string_vect types, _functions &funcList){
    try{
        _function func(initFunction(source));
        if(!conformity_to_all_types(func.type,types)){
            throw "error function type";
        }
    }
    catch(const char * _error_message){
        printf("%s\n", _error_message);
    }
}