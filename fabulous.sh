#!/bin/bash

#mnk-game-test
#Following repository: https://github.com/martialdidit/mnk-game-test
#Martial Puygrenier - martialdidit
#last update : 18/10/2014

STARTTIME=$(date +%s)
declare pass=0
declare fail=0

total=148

red='\e[41m'
blue='\e[1;34m'
purple='\e[1;31m'
yellow='\e[43m'
NC='\e[0m' # No Color
bold=`tput bold`
normal=`tput sgr0`

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
function constest {
    
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
        echo "Check the file $FILE"
        echo "Stdin :"
        while read -r line
        do
            echo $line
        done <$FILE
        while read -r line
        do
            cat <<< "$line"
        done <$FILE | "$@"
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
make &>/dev/null
code=$?
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
make help &>/dev/null
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

for i in "$@"
do
case $i in
        -s)
        #Basic test
        while read line
        do
            name=$line
            fabulous $name
        done < sample_test

    ;;
        -g)
        #Grid test
        while read line
        do
            name=$line
            game $name
        done < grid_test
    ;;
        -c)
        #Constest test
        while read line
        do
            name=$line
            constest $name
        done < test_contest
    ;;
        -b)
        #board tests
        make
        ./bitboard_test
        pass=$((pass+45))
    ;;
    *)
        echo "Unkknow option, see the readme"
        exit
    ;;
esac
done

ENDTIME=$(date +%s)

echo ""
echo "----------( Final result )----------"
echo -e "${blue}Passed $pass${NC}; ${red}Failed: $fail${NC}; Total $total tests"
if [[ $((pass + fail)) -ne $total ]]; then 
    echo -e "${purple}CAREFUL, NOT ALL THE TEST ARE PASSED IN THE SCRIPT${NC}, can be an infinite loop or you simply forget to add the test files."
fi
echo "Time elapsed: $((ENDTIME-STARTTIME))s"

