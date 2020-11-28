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
    is_var = 0, is_func
};

_action getActionType(std::string codeLIne, WPTool::string_vect _types);
_init getInitType(std::string codeLIne);

#endif