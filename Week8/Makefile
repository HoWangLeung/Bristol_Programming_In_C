CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g3 
SANITIZE= -fsanitize=undefined -fsanitize=address
LDLIBS=-lm
FILE=rollarboard
TXT=d.rbd


all: ${FILE}
${FILE}: ${FILE}.c
	$(CC) ${FILE}.c -o ${FILE} ${CFLAGS}  ${LDLIBS}
val: ${FILE}
	valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all  ./${FILE} ${TXT}
r: ${FILE}
	./${FILE} ${TXT}
v: ${FILE}
	./${FILE} -v ${TXT}

#-fsanitize=address 
#--log-file="valgrind" 