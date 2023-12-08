#pragma once

#include "config.h"
#include <sstream>

#ifndef PASTA_ERROR_H
#define PASTA_ERROR_H

PASTA_NAMESPACE_START

struct error {
private:
    void say( std::string e ) const {
        std::cerr << "Copypasta: " << e << std::endl;
    }

public:
    void double_mode() const noexcept {
        say( "Cannot set pasta mode twice in same runtime." );
    }

    void invalid_arg( const std::string &arg ) const noexcept {
        say( "Invalid argument: " + arg );
    }
    void invalid_arg( const char &arg ) const noexcept {
        std::string c = { arg };
        say( "Invalid argument: " + c );
    }

    void mismatch_arg( const size_t &a, const size_t &b ) const noexcept {
        std::stringstream err;
        err << "Mismatch between arguments (" << a << ") vs parameters (" << b << ")" << std::endl;
        say( err.str() );
    }

    void invalid_reg( const std::string &arg ) const noexcept {
        say( "Invalid argument: " + arg );
    }

    void no_reg() {
        say( "No register has been specified" );
    }
};

PASTA_NAMESPACE_END

#endif // PASTA_ERROR_H
