mnk-game-test
=============

Automatic test of the mnk-game 



### 1) How to use the script ? 

Go to the parent folder of the `mnk-game/` directory
```
git clone https://github.com/martialdidit/mnk-game-test.git
cd mnk-game-test
chmod +x fabulous.sh
```

You can now launch the tests regarding what you want to test !
```
-s : file sample_test -> just check the basic tests of TP1
-g : file grid_test -> the tests of the TP2 & some of TP3
-c : file test_contest -> tests of the contest mode
```
There is also valgrind tests in the script ! 

Launch the **./fablulous** test with only one option:
```
./fabulous.sh -s #or -g -c
```
All options:

```
./fabulous.sh -s -g -c
```

Enjoy ! 

### 2) See the results

If there is an error you will the error code, and the output error of your mnk-game.
At the end of the script you will see your score !

Some time, just run the script twice if you have a valgrind error with option -V


### 3) Particapte

If you want to improve this script, feel free to create a pull request
