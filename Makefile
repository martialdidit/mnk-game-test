EXEC=bitboard_test

CFLAGS=-g -Wall -Wextra -std=c99 
CPPFLAGS=-I../mnk-game/include -I../mnk-game/src -DDEBUG
LDFLAGS=-lm

.PHONY: all clean

all: $(EXEC)

$(EXEC):  bitboard_test.c ../mnk-game/src/board.c ../mnk-game/include/board.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-rm -f *.o *~ $(EXEC)