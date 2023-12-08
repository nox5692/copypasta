#include <iostream>

#include "app.h"
#include "config.h"

int main( int arg_cnt, char **args ) {

    pasta::app runtime( arg_cnt, args );
    if ( !runtime.pair_registers() )
        return EXIT_FAILURE;
    runtime.run();

    return EXIT_SUCCESS;
}
