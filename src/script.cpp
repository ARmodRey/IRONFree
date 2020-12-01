#include "script.h"

script::script(std::string script_file){
    _source = new FSTool::file(script_file);
}

script::~script(){
    delete _source;
}

bool script::cheskScript(){
    return (_source->exists() && !_source->empty());
}

void script::runScript(){
    // for(int i = 0; i < _source->get_info().size; i++){
    //     std::string sourceLine = _source->get(i);
    //     if(sourceLine.empty()){
    //         continue;
    //     }
    //     WPTool::string_content scriptLine(sourceLine, ";");
    //     if(scriptLine.get_size() > 0){
    //         for(int j = 0; j < scriptLine.get_size(); j++){
    //             if(getActionType(scriptLine[j], _types) == is_init){
    //                 if(getInitType(scriptLine[j]) == _var){
    //                     if(scriptLine.have("{") && !scriptLine.have("}")){
    //                         std::string codeContent = scriptLine[j] + getContentBetween('{', '}', i);
    //                         varInitInterpretation(codeContent, _types,initVars);
    //                     }
    //                     else{
    //                         varInitInterpretation(scriptLine[j],_types,initVars);
    //                     }
    //                 }
    //                 if(getInitType(scriptLine[i]) == _func){
    //                     if(scriptLine.have("{") && !scriptLine.have("}")){
    //                         std::string codeContent = scriptLine[j] + getContentBetween('{', '}', i);
    //                         funcInitInterpretation(codeContent, _types,initFuncs);
    //                     }
    //                     else{
    //                         funcInitInterpretation(scriptLine[j],_types,initFuncs);
    //                     }
    //                 }
    //             }
    //             if(getActionType(scriptLine[i], _types) == is_empl){
                    
    //             }
    //             if(getActionType(scriptLine[i], _types) == is_use){
                    
    //             }
    //         }
    //     }
    // }
}

std::string script::getContentBetween(char start, char end, int & filePos){
    std::string result;
    int endStrPos = _source->find(std::to_string(end),filePos); // получение позиции с конечным символом
    while (true){
        if(_source->find(std::to_string(start),filePos,endStrPos) != -1){
            endStrPos = _source->find(std::to_string(end),endStrPos + 1);
        }
        else{
            break;
        }
    }
    for(int i = filePos + 1; i < endStrPos; i++){
        result += _source->get(i);  
    }
    filePos = endStrPos;
    return result;
}