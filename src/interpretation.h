#ifndef __INTERPRT__H__
#define __INTERPRT__H__

#include "math.h"
#include "units.h"
#include "initialization.h"
#include "processing.h"

// клас для интерпритации части кода 
class interpreter{
private:
    int findVarFromName(std::string varName);        // поиск переменной по названию
    int findFuncFromName(std::string funcName);
    void varInitInterpretation(std::string source);  // интерпритация инициализация переменной
    void varInitErr(_variable var);                  // проверка на ошибки в инициализации
    void funcInitErr(_function func);                // проверка на ошибки в инициализации 
    void numVarInitIterpr(_variable &var);           // проверка на ошибки в инициализации
    double getResultOfExp(std::string exp);          // вычисленние значения из выражения
    std::string valueCodeResult(std::string codeLine); // получения результата небольшого кусочка кода
    void funcInitInterpretation(std::string source); // интерпритация обьявления функции
    std::string getFuncResult(std::string source);   // получение результата функции
    _variables varList;                              // инициализированные переменные
    _functions funcList;                             // инициализированные функции
    std::string source;                              // код для интерпритации
    WPTool::string_vect _types { "file", "folder", "str", "num", "proc"}; // типы данных
    _action interpT;     // тип интерпритации
    int actionType;
public:
    interpreter(std::string source, _variables varList, _functions funcList);
    void update(_variables &varList, _functions &funcList);
    void setTypeOfInterpritation(_action action, int actionType);
    void start();
};



#endif 