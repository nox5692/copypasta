#pragma once

#include "config.h"

PASTA_NAMESPACE_START

enum reg : size_t {};

enum mode : char {
    copy  = 'c',
    paste = 'p',
    list = 'l',
    clear = 'k',
    unset = '@',
};

#define MODE_LIST_VAL "list"
#define MODE_CLEAR_VAL "clear"

PASTA_NAMESPACE_END
