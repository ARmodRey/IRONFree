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
    for(int i = 0; i < _source->get_info().size; i++){
        std::string sourceLine = _source->get(i);
        if(sourceLine.empty()){
            continue;
        }
        WPTool::string_content scriptLine(sourceLine, ";");
        if(scriptLine.get_size() > 0){
            for(int j = 0; j < scriptLine.get_size(); j++){
                
            }
        }
    }
}