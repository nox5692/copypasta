#pragma once

#include <cctype>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "config.h"
#include "enum.h"
#include "error.h"

#ifndef PASTA_APP_H
#define PASTA_APP_H

PASTA_NAMESPACE_START

class app {
    std::vector<std::string> _args;
    std::map<reg, std::string> _reg_pairs;
    std::vector<reg> _regs_active;
    mode _pasta_mode;

public:
    app( int &arg_cnt, char **args ) : _args( arg_cnt ), _reg_pairs(), _pasta_mode( unset ) {
        for ( int i = 0; i < arg_cnt; i++ )
            _args[i] = args[i];
    }

    bool pair_registers() noexcept {
        std::vector<std::string> paths_active;
        pasta::error e; // Potential error classs
        for ( const auto &argument : _args ) {
            if ( argument.size() < 2 )
                continue;
            if ( argument == _args[0] )
                continue;
            if ( argument[0] == ARG_START && argument[1] == ARG_START ) {
                std::string word_arg = argument.substr( 2 );
                if ( word_arg == MODE_LIST_VAL )
                    _pasta_mode = list;
                if ( word_arg == MODE_CLEAR_VAL )
                    _pasta_mode = clear;
                return true;
            }
            if ( argument[0] == ARG_START ) {
                for ( const auto &c : argument ) {
                    if ( c == argument[0] )
                        continue;
                    if ( c == mode::copy ) {
                        if ( _pasta_mode == unset ) {
                            _pasta_mode = mode::copy;
                            continue;
                        }
                        e.double_mode();
                        return false;
                    }
                    if ( c == mode::paste ) {
                        if ( _pasta_mode == unset ) {
                            _pasta_mode = mode::paste;
                            continue;
                        }
                        e.double_mode();
                        return false;
                    }
                    if ( std::isdigit( c ) ) {
                        _regs_active.push_back( (reg)( c - '0' ) );
                        continue;
                    }
                    e.invalid_arg( c );
                }
                continue;
            }
            paths_active.push_back( argument );
        }

        if ( _pasta_mode == copy ) {
            if ( _regs_active.size() != paths_active.size() ) {
                e.mismatch_arg( _regs_active.size(), paths_active.size() );
                return false;
            }

            for ( size_t i = 0; i < _regs_active.size(); i++ ) {
                _reg_pairs[_regs_active[i]] = paths_active[i];
            }
            return true;
        }

        // If unset -> paste

        return true;
    }

    bool run() const noexcept {
        pasta::error e;

        if ( _pasta_mode == clear ) {
            fs::path dir( PASTA_GLOBAL_PATH );
            std::string suff( PASTA_GLOBAL_SUFFIX );
            for ( const auto &entry : fs::directory_iterator( dir ) ) {
                if ( entry.is_regular_file() && entry.path().extension() == suff ) {
                    std::string syscall = "rm -f " + entry.path().string();
                    system( syscall.c_str() );
                }
            }

            return true;
        }

        if ( _pasta_mode == list ) {
            fs::path dir( PASTA_GLOBAL_PATH );
            std::string suff( PASTA_GLOBAL_SUFFIX );
            for ( const auto &entry : fs::directory_iterator( dir ) ) {
                if ( entry.is_regular_file() && entry.path().extension() == suff ) {
                    std::ifstream file( entry.path() );
                    std::string line;
                    while ( std::getline( file, line ) ) {
                        std::cout << entry << ": " << line << std::endl;
                    }
                }
            }

            return true;
        }

        if ( _pasta_mode == copy ) {
            for ( const auto &reg_pair : _reg_pairs ) {
                std::stringstream ss;
                ss << reg_pair.first;
                std::string reg_num;
                ss >> reg_num;
                std::string s = PASTA_GLOBAL_PATH;
                s += reg_num;
                s += ".pasta";
                std::ofstream reg_file( s, std::ios::out );
                fs::path abs_path( reg_pair.second );
                reg_file << fs::absolute( abs_path ).c_str();
            }
            return true;
        }

        for ( const auto &reg : _regs_active ) {
            std::stringstream ss;
            ss << reg;
            std::string s = PASTA_GLOBAL_PATH;
            std::string reg_num;
            ss >> reg_num;
            s += reg_num;
            s += ".pasta";

            fs::path reg_path( s );
            if ( !fs::is_regular_file( reg_path ) ) {
                e.invalid_arg( reg_num );
                return false;
            }

            std::ifstream reg_file( s, std::ios::in );
            std::string original_path;
            reg_file >> original_path;

            std::string syscall = "cp -r " + original_path + " . ";
            system( syscall.c_str() );
        }

        return true;
    }
};

PASTA_NAMESPACE_END

#endif // PASTA_APP_H
