# Colors:
COLOR_BLACK='\033[0;30m'
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_YELLOW='\033[0;33m'
COLOR_BLUE='\033[0;34m'
COLOR_MAGENTA='\033[0;35m'
COLOR_CYAN='\033[0;36m'
COLOR_WHITE='\033[0;37m'
COLOR_RESET='\033[0m'

# Compilator assets
CC=g++
CFLAGS=-Wall\ -std=c++17\ -pedantic\ -g\ -fsanitize=address
SRC_DIR=src
CFILES=$(ls $SRC_DIR)
OBJ_DIR=obj
OBJ_ARR=()
TAR_DIR="$PWD"
TAR_FILE=pasta

if [ $# -eq 0 ]; then

    mkdir -p $OBJ_DIR
    mkdir -p $TAR_DIR

    echo "${COLOR_YELLOW}Compiling... ${COLOR_RESET}"
    for F in $CFILES; do
        if [ $(echo $F | cut -d. -f2) == "cpp" ]; then
            OBJ_FILE=$(echo $F | cut -d. -f1)
            $CC $CFLAGS -DPASTA_GLOBAL_PATH=\"$PWD/\" -c $SRC_DIR/$F -o $OBJ_DIR/$OBJ_FILE.o
            if [ $? -eq 1 ]; then
                echo "${COLOR_RED}Compilation failed.${COLOR_RESET}"
                exit 1
            fi
            OBJ_ARR+="$OBJ_DIR/$OBJ_FILE.o "
        fi
    done
    if [ $? -eq 0 ]; then
        echo "${COLOR_GREEN}Compilation succesful!${COLOR_RESET}"
    else
        echo "${COLOR_RED}Compilation failed.${COLOR_RESET}"
    fi

    echo "${COLOR_YELLOW}Linking... ${COLOR_RESET}"
    $CC $CFLAGS -DPASTA_GLOBAL_PATH=\"$PWD/\" $OBJ_ARR -o $TAR_DIR/$TAR_FILE
    if [ $? -eq 0 ]; then
        echo "${COLOR_GREEN}Linking succesful!${COLOR_RESET}"
        sudo mkdir -p /usr/local/bin && 
        if [ ! -e /usr/local/bin/$TAR_FILE ]; then
            sudo ln -s $PWD/$TAR_FILE /usr/local/bin/$TAR_FILE
        fi
    else
        echo "${COLOR_RED}Linking failed.${COLOR_RESET}"
    fi

elif [ $1 == "run" ] || [ $1 == "r" ]; then # ! UNSTABLE !
    if [ -f "$TAR_DIR/$TAR_FILE" ]; then
        ./${TAR_DIR}/${TAR_FILE}
    else
        echo "${COLOR_RED}Executable not found.${COLOR_RESET}"
    fi
elif [ $1 == "clean" ] || [ $1 == "clear" ] || [ $1 == "c" ] || [ $1 == "del"] || [$1 == "d" ]; then
    rm -rf $TAR_FILE $OBJ_DIR
    echo "${COLOR_YELLOW}Removed compilation assets.${COLOR_RESET}"
else
    echo "${COLOR_RED}Invalid command.${COLOR_RESET}"
fi
