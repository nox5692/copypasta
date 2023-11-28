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
#define PASTA_GLOBAL_PATH "/Users/danvychytil/Code/C:C++/copypasta/"
#define PASTA_GLOBAL_SUFFIX ".pasta"

#endif // PASTA_CONFIG_H
