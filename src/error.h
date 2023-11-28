#pragma once

#include "config.h"

#ifndef PASTA_ERROR_H
#define PASTA_ERROR_H

PASTA_NAMESPACE_START

struct error {
    void double_mode() {
        std::cout << "Cannot set pasta mode twice in same runtime." << std::endl;
    }

    void invalid_arg( const std::string &arg ) const noexcept {
        std::cout << "Invalid argument: " << arg << std::endl;
    }
    void invalid_arg( const char &arg ) const noexcept {
        std::cout << "Invalid argument: " << arg << std::endl;
    }

    void mismatch_arg( const size_t &a, const size_t &b ) const noexcept {
        std::cout << "argc: " << a << " vs. "
                  << "pathc: " << b << std::endl;
    }

    void invalid_reg( const std::string &arg ) const noexcept {
    }
};

PASTA_NAMESPACE_END

#endif // PASTA_ERROR_H
