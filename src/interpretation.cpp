#include "interpretation.h"

interpreter::interpreter(std::string source, _variables varList, _functions funcList){
    this->source = source;
    this->varList = varList;
    this->funcList = funcList;
}

void interpreter::update(_variables &varList, _functions &funcList){
    varList = this->varList;
    funcList = this->funcList;
}

void interpreter::setTypeOfInterpritation(_action action, int actionType){
    this->actionType = actionType;
    interpT = action;
}

void interpreter::start(){
    if(interpT == is_init){
        if(actionType == _var){
            varInitInterpretation(this->source);
        }
        if(actionType == _func){
            funcInitInterpretation(this->source);
        }
    }
    if(interpT == is_empl){
    
    }
    if(interpT == is_use){
    
    }
}

int interpreter::findVarFromName(std::string varName){
    WPTool::string_content name(varName,"[].");
    for(_variables::iterator _varIT = this->varList.begin(); _varIT != this->varList.end(); ++_varIT){
        if(_varIT->name == name.get(0) ){
            return std::distance(this->varList.begin(), _varIT);
        }
    }
    return -1;
}

void interpreter::varInitErr(_variable var){
    if(findVarFromName(var.name) != -1){
        throw "same variable names";
    }
    for(_functions::iterator _funcIT = this->funcList.begin(); _funcIT != this->funcList.end(); ++_funcIT){
        if(_funcIT->name == var.name){
            throw "function with the same name has already been declared";
        }
    }
    if(!conformity_to_all_types(var.type,_types)){
        throw "error var type";
    }
}

void interpreter::varInitInterpretation(std::string source){
    _variable var(initVariable(source));
    varInitErr(var);
    if(var.type == "num"){ // инициализация переменной типа num
        numVarInitIterpr(var); // вносим переменную в память и проверяем ее значение 
    }
    varList.push_back(var);   
}

std::string interpreter::valueCodeResult(std::string codeLine){
     _variable foundVar = varList[findVarFromName(codeLine)];
    if(foundVar.type.find("list") != std::string::npos){
        WPTool::string_content line(codeLine,"[]");
        return foundVar.properties["object" + line.get(1)];
    }
    else{
        return foundVar.properties["object0"];
    }
}

void interpreter::numVarInitIterpr(_variable &var){
    if(var.properties.size() == 1 ){
        if(var.properties["object0"].find_first_of("+-*/") != std::string::npos){
            double expRes = getResultOfExp(var.properties["object0"]);
            std::string val = std::to_string(expRes);
            int lastZeroPos = 0;
            for(size_t i = val.size() - 1; i != val.find(".") - 1; i--){
                if(val[i] != '0'){
                    
                    lastZeroPos = i;
                    break;
                }
            }
            var.properties.erase("object0");
            var.properties["object0"] = val.substr(0,lastZeroPos+1);
        } 
        else if(findVarFromName(var.properties["object0"]) != -1 ){
           var.properties["object0"] = valueCodeResult(var.properties["object0"]);
        }
        else if(!WPTool::is_digit(var.properties["object0"])){
            throw var.properties["object0"] +  " --> is not digit"; 
        }
    }
    if(var.properties.size() > 1 ){
        throw "wrong number of parameters";
    }
}

double interpreter::getResultOfExp(std::string exp){
    std::string exps = exp;
    WPTool::string_content nums(exps,"+-*/");
    bool findVars = true;
    while(findVars != false){
        findVars = false;
        for(int i = 0; i < nums.get_size(); i++){
            if(findVarFromName(nums[i]) != -1){
                findVars = true;
                castingNumExpressions(exps);
                nums.set_string(exps);
            }
        }
    }
    double value = 0;
    WPTool::string_content chars(exps,"1234567890.,abcdefghijklmnopqrstuvwxyz[]");
    value += std::stof(nums[0].c_str()); 
    for(int i = 1; i < nums.get_size(); i++){
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

void interpreter::castingNumExpressions(std::string & exp){
    WPTool::string_content nums(exp,"+-*/");
    for(int i = 0; i < nums.get_size(); i++){
        if (findVarFromName(nums[i]) != -1){
            nums.edit(i,valueCodeResult(nums[i]));
        }
        // if (getEmplType(nums[i]) == _use_func){
        //     nums.edit(i,getFuncResult(nums[i]));
        // } 
    }
    exp = nums.get_string();
}

// void interpreter::listVarInitInterpr(_variable &var){
//     for(auto propItr = var.properties.begin(); propItr != var.properties.end(); propItr++){

//     }
// }

void interpreter::funcInitInterpretation(std::string source){
    _function func(initFunction(source));
    funcInitErr(func);
    funcList.push_back(func);
}

void interpreter::funcInitErr(_function func){
    if(!conformity_to_all_types(func.type,_types)){
        throw "error function type";
    }
    if(findFuncFromName(func.name) != -1){
        throw "same function names";
    }
    if(findVarFromName(func.name) != -1){
        throw "variable with the same name has already been declared";
    }   
}

int interpreter::findFuncFromName(std::string funcName){
    for(_functions::iterator _funcIT = this->funcList.begin(); _funcIT != this->funcList.end(); ++_funcIT){
        if(_funcIT->name == funcName){
            return std::distance(funcList.begin(), _funcIT);
        }
    }
    return -1;
}