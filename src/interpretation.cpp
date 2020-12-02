#include "interpretation.h"

int findVarFromName(std::string varName, _variables varList){
    for(_variables::iterator _varIT = varList.begin(); _varIT != varList.end(); ++_varIT){
        if(_varIT->name == varName ){
            return std::distance(varList.begin(), _varIT);
        }
    }
    return -1;
}

void varInitErr(_variable var, _variables & varList){
    if(findVarFromName(var.name,varList) != -1){
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
    catch(std::string _error_message){
        printf("%s\n", _error_message.c_str());
    }
}

void numVarInitIterpr(_variable &var, _variables varList){
    if(var.properties.size() == 1 ){
        if(findVarFromName(var.properties["object0"],varList) != -1 ){
            std::string * name = new std::string(var.name);
            var = varList[findVarFromName(var.properties["object0"],varList)];
            var.name = *name;
            delete name;
        }
        else if(var.properties["object0"].find_first_of("+-*/") != std::string::npos){
            double expRes = getResultOfExp(var.properties["object0"], varList);
            std::string objStr = std::to_string(expRes);
            size_t zeroPosStart = objStr.find_first_of("0",objStr.find_first_of(".")) - 1;
            var.properties.erase("object0");
            var.properties["object0"] = objStr.substr(0,objStr.size() - zeroPosStart);
        }
        else if(!WPTool::is_digit(var.properties["object0"])){
            throw var.properties["object0"] +  " --> is not digit"; 
        }
    }
    if(var.properties.size() > 1 ){
        throw "wrong number of parameters"
    }
}

double getResultOfExp(std::string exp, _variables varList){
    WPTool::string_content nums(exp,"+-*/");
    WPTool::string_content chars(exp,"1234567890.,abcdefghijklmnopqrstuvwxyz");
    double value = 0;
    if(findVarFromName(nums[0],varList) != -1){
        nums.edit(0,varList[findVarFromName(nums[0],varList)].properties["object0"]);
    }
    value += std::stof(nums[0].c_str()); 
    for(int i = 1; i < nums.get_size(); i++){
        if (findVarFromName(nums[i],varList) != -1){
            nums.edit(i,varList[findVarFromName(nums[i],varList)].properties["object0"]);
        }
        if (!WPTool::is_digit(nums[i])){
            throw nums[i] + " --> is not variable"; 
        }
        switch (chars[i-1][0]){
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
    return value;
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