#!/bin/bash

#mnk-game-test
#Following repository: https://github.com/martialdidit/mnk-game-test
#Martial Puygrenier - martialdidit
#last update : 08/10/2014

if [ -z "$1" ]
  then
    echo "file sample_test missing"
    exit
fi
if [ -z "$2" ]
  then
    echo "file grid_test missing"
    exit
fi

STARTTIME=$(date +%s)
declare pass=0
declare fail=0

red='\e[41m'
blue='\e[1;34m'
NC='\e[0m' # No Color

function failed {
  fail=$((fail+1))
}
function success {
  pass=$((pass+1))
}

function fabulous {
    
    EXPECT_VALUE=$1
    shift
    "$@" &>/dev/null
    local status=$?
    if [ $EXPECT_VALUE -eq 0 ]; then
      echo "Expected result: EXIT_SUCCESS"
    else
      echo "Expected result: EXIT_FAILURE"
    fi
    if [ $status -eq $EXPECT_VALUE ]; then
        echo -e "${blue}*Passed*${NC}: check $@"
        success
    else
        echo -e "${red}****FAILED!****:${NC} check $@"
        echo ""
        echo "Return code: $status (Error)"
        echo "Stderr"
        "$@"
        failed
    fi
    echo ""
}
function game {

    EXPECT_VALUE=$1
    shift
    FILE=$1
    shift
    while read -r line
    do
        cat <<< "$line"
    done <$FILE | "$@" &>/dev/null

    local status=$?
    if [ $EXPECT_VALUE -eq 0 ]; then
      echo "Expected result: EXIT_SUCCESS"
    else
      echo "Expected result: EXIT_FAILURE"
    fi
    if [ $status -eq $EXPECT_VALUE ]; then
        echo -e "${blue}*Passed*${NC}: check $@"
        success
    else
        echo -e "${red}****FAILED!****:${NC} check $@"
        echo ""
        echo "Return code: $status (Error)"
        echo "Stderr"
        "$@"
        failed
    fi
    echo ""
}


echo "=======================[ mnk-game ]========================="
echo ""
echo "-----------( File Hierarchy )---------"
echo ""
if [ ! -f ../mnk-game/src/mnk-game.c ]; then
    echo "File '../mnk-game/src/mnk-game.c' not found!"
    failed
fi
if [ ! -f ../mnk-game/src/mnk-game.h ]; then
    echo "File '../mnk-game/src/mnk-game.h' not found!"
    failed
fi
if [ ! -f ../mnk-game/src/Makefile ]; then
    echo "File '../mnk-game/src/MAKEFILE' not found!"
    failed
fi
if [ ! -f ../mnk-game/Makefile ]; then
    echo "File '../mnk-game/MAKEFILE' not found!"
    failed
fi

if [ $fail -eq 0 ]; then
    echo "Checking request files: Passed"
else
    echo "Checking request files: Failed"
fi

echo ""
echo "-----------( Build System )---------"
echo ""

cd ../mnk-game
echo "Expected result: EXIT_SUCCES"
make 2>/dev/null
code=$?
echo $code
if [[ $code -eq 0 ]]; then
    echo "*Passed*: check the make"
    success
else
    echo "****FAILED!****: check the make target"
    echo "Abort the script"
    failed
    exit
fi
echo ""
make --help 2>/dev/null
code=$?
echo "Expected result: EXIT_SUCCES"
if [[ code -eq 0 ]]; then
    echo "*Passed*: check the help target"
    success
else
    echo "****FAILED!****: check the help target"
    failed
fi

if [[ ! -f ../mnk-game/mnk-game ]]; then
    echo "****FAILED!****: executable not found"
    echo "Abort the script"
    failed
    exit 
fi  

echo ""
echo "-----------( Option Parser )---------"
echo ""

cd ../mnk-game-test

#Basic test
while read line
do
    name=$line
    fabulous $name
done < $1

#Grid test
while read line
do
    name=$line
    game $name
done < $2

ENDTIME=$(date +%s)

echo ""
echo "----------( Final result )----------"
echo -e "${blue}Passed $pass${NC}; ${red}Failed: $fail${NC}"
echo "Time elapsed: $((ENDTIME-STARTTIME))s"

