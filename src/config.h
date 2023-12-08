#pragma once

#include <iostream>

#ifndef PASTA_CONFIG_H
#define PASTA_CONFIG_H

// Namespace pasta guards
#define NAMESPACE_NAME pasta
#define PASTA_NAMESPACE_START namespace NAMESPACE_NAME {
#define PASTA_NAMESPACE_END }

// Shorten filesystem namespace
namespace fs = std::filesystem;

#define ARG_START '-'
#define PASTA_GLOBAL_SUFFIX ".pasta"
#ifndef PASTA_GLOBAL_PATH
    #define PASTA_GLOBAL_PATH "~" // Default definition
#endif


// ANSI escape code for text color
#define CLR_RESET "\033[0m"
#define CLR_BLACK "\033[30m"
#define CLR_RED "\033[31m"
#define CLR_YELLOW "\033[33m"
#define CLR_BLUE "\033[34m"
#define CLR_MAGENTA "\033[35m"
#define CLR_CYAN "\033[36m"
#define CLR_WHITE "\033[37m"
#define CLR_BOLD "\033[1m"
#define CLR_UNDERLINE "\033[4m"
#define CLR_BG_BLACK "\033[40m"
#define CLR_BG_RED "\033[41m"
#define CLR_BG_GREEN "\033[42m"
#define CLR_BG_YELLOW "\033[43m"
#define CLR_BG_BLUE "\033[44m"
#define CLR_BG_MAGENTA "\033[45m"
#define CLR_BG_CYAN "\033[46m"
#define CLR_BG_WHITE "\033[47m"

#endif // PASTA_CONFIG_H
