#ifndef __SCRIPT__H__
#define __SCRIPT__H__

#include "FSTool.h"
#include "units.h"
#include "initialization.h"
#include "processing.h"
#include "interpretation.h"


class script{
private:
    WPTool::string_vect _types {  // типы данных 
        "file", "folder", "str", "num", "proc"
    };   
    WPTool::string_vect useFiles; // включаемые файлы
    _functions initFuncs;         // инициализированные функции
    _variables initVars;          // инициализированные переменные
    FSTool::file *_source;        // файл с исходным кодом
    std::string getContentBetween(char start, char end, int & filePos); //получение данных из файла между позициями
public: 
    script(std::string script_file);
    void runScript();
    bool cheskScript();
    ~script();
};

#endif