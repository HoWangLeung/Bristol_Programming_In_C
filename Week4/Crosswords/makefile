CC=clang
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -O1 -Werror
LDLIBS= -lm
FILE=crossword
crossword : crossword.c cwddriver.c crossword.h
	$(CC) crossword.c cwddriver.c -o crossword $(CFLAGS) $(LDLIBS)
val: ${FILE}
	valgrind --leak-check=full --track-origins=yes  ./${FILE}