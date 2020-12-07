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
    for(int i = 0; i < _source->get_info().lines; i++){
        std::string sourceLine = _source->get(i);
        if(sourceLine.empty()){
            continue;
        }
        WPTool::string_content codeStr(sourceLine,";");
        int lineAction = getActionType(sourceLine,_types);
        interpreter * intprLine;
        try{
            if(lineAction == is_init){
                int initType = getInitType(sourceLine);
                int filePos = i;
                if(codeStr.have("{") && !codeStr.have("}")){
                    intprLine = new interpreter(sourceLine + getContent(i), initVars, initFuncs);
                }
                else{
                    intprLine = new interpreter(sourceLine, initVars, initFuncs);
                }
                intprLine->setTypeOfInterpritation(is_init,initType);
                intprLine->start();
                intprLine->update(initVars,initFuncs);
                if(initType == _func){
                    initFuncs[initFuncs.size() - 1].startPos = filePos;
                    initFuncs[initFuncs.size() - 1].endPos = i;
                }
                delete intprLine;
            }
        }
        catch(const char * _error_message){
            printf("line %i:%s\n", i,  _error_message);
        }    
        catch(std::string _error_message){
            printf("line %i:%s\n", i, _error_message.c_str());
        }
    }
}

std::string script::getContent(int & filePos){
    std::string result;
    int openChars = 0;
    int *tempOpen = new int;
    int *tempClose = new int;
    int endStrPos;
    *tempOpen = _source->find("{",filePos); 
    *tempClose = _source->find("}",filePos);
    while (*tempOpen < *tempClose){
        openChars++;
        *tempClose = _source->find("}",filePos); // получение позиции с конечным символом    
        *tempOpen = _source->find("{",*tempOpen + 1);// получение позиции с начальным символом
        if(*tempOpen == -1){
            break;
        }
    }
    delete tempOpen;
    delete tempClose;
    for(int i = 0; i != openChars; i++){
        endStrPos = _source->find("}",filePos); // получение позиции с конечным символом
    }
    for(int i = filePos + 1; i < endStrPos; i++){
        result += _source->get(i);  
    }
    filePos = endStrPos + 1;
    return result;
}