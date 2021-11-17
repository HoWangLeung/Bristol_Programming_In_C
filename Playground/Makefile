CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g3
LDLIBS=-lm
FILE=test



all: ${FILE}
${FILE}: ${FILE}.c
	$(CC) ${FILE}.c -o ${FILE} ${CFLAGS} ${LDLIBS}
val: ${FILE}
	valgrind --leak-check=full --track-origins=yes  ./${FILE}
r: ${FILE}
	./${FILE}

