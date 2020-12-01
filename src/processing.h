#ifndef __PROCS__H__
#define __PROCS__H__

#include "units.h"
#include "initialization.h"
#include "WPTool.h"
#include "FSTool.h"

enum  _action {
    is_init = 0, is_empl, is_use
};

enum _init {
    _var = 0, _func
};

enum _empl{
    _ins = 0, _use_func, _add_val
};

_action getActionType(std::string codeLIne, WPTool::string_vect _types);
_init getInitType(std::string codeLIne);
_empl getEmplType(std::string codeLine);

#endif