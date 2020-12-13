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
        try{
            if(lineAction == is_init){
                interpreter * intprLine;
                int initType = getInitType(sourceLine);
                int filePos = i;
                if(codeStr.have("{") && !codeStr.have("}")){
                    intprLine = new interpreter(getContent(i), initVars, initFuncs);
                }
                else{
                    intprLine = new interpreter(sourceLine, initVars, initFuncs);
                }
                intprLine->setTypeOfInterpritation(is_init,initType);
                intprLine->start();
                intprLine->update(initVars,initFuncs);
                if(initType == _func){
                    initFuncs[initFuncs.size() - 1].startPos = filePos;
                    initFuncs[initFuncs.size() - 1].endPos = i - 1;
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
    int closeChars = 0;
    for(int i = filePos; i < _source->get_info().lines; i++){
        std::string *temp = new std::string(_source->get(i));
        printf("%s\n" , temp->c_str());
        if(temp->length() == 0){
            delete temp;
            continue;
        }
        result += *temp;
        if(temp->find("{") != std::string::npos){
            openChars++;
        }
        if(temp->find("}") != std::string::npos){
            closeChars++;
        }
        printf("o: %i  c%i\n", openChars, closeChars);
        delete temp;
        if(closeChars == openChars){
            filePos = i + 1;
            break;
        }
    }
    return result;
}