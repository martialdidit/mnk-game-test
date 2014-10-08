#!/bin/bash

#mnk-game-test
#Following repository: https://github.com/martialdidit/mnk-game-test
#Martial Puygrenier - martialdidit
#last update : 07/10/2014

STARTTIME=$(date +%s)
declare pass=0
declare fail=0

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
        echo "*Passed*: check $@"
        success
    else
        ERROR=$("$@" 2>&1 >/dev/null)
        echo "****FAILED!****: check $@"
        echo ""
        echo "Return code: $status (Error)"
        echo "Stderr"
        echo $ERROR
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
    done <te | "$@" &>/dev/null

    local status=$?
    if [ $EXPECT_VALUE -eq 0 ]; then
      echo "Expected result: EXIT_SUCCESS"
    else
      echo "Expected result: EXIT_FAILURE"
    fi
    if [ $status -eq $EXPECT_VALUE ]; then
        echo "*Passed*: check $@"
        success
    else
        ERROR=$("$@" 2>&1 >/dev/null)
        echo "****FAILED!****: check $@"
        echo ""
        echo "Return code: $status (Error)"
        echo "Stderr"
        echo $ERROR
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

echo "Expected result: EXIT_SUCCES"
$(make) 2>/dev/null
code=$?
if [[ $code -ne 0 ]]; then
    echo "*Passed*: check the make"
    success
else
    echo "****FAILED!****: check the make target"
    echo "Abort the script"
    failed
    exit
fi
echo ""
$(make --help) 2>/dev/null
code=$?
echo "Expected result: EXIT_SUCCES"
if [[ code -ne 0 ]]; then
    echo "*Passed*: check the help target"
    success
else
    echo "****FAILED!****: check the help target"
    failed
fi

echo ""
echo "-----------( Option Parser )---------"
echo ""

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
echo "Passed $pass; Failed: $fail"
echo "Time elapsed: $((ENDTIME-STARTTIME))s"

