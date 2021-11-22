CC=clang
CFLAGS=-Wall -Wextra  -pedantic -std=c99  -g3  
SANITIZE= -fsanitize=undefined -fsanitize=address 
LDLIBS=-lm
FILE=rollerboard
TXT=6x6m4.rbd
EXT=extension

all: ${FILE}
${FILE}: ${FILE}.c
	$(CC) ${FILE}.c -o ${FILE} ${CFLAGS}  ${LDLIBS}
val: ${FILE}
	valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all  ./${FILE} ${TXT}
r: ${FILE}
	./${FILE} ${TXT}
v: ${FILE}
	./${FILE} -v ${TXT}
e: ${EXT}
${EXT}: ${EXT}.c
	$(CC) ${EXT}.c -o ${EXT} ${CFLAGS} ${LDLIBS}
re:${EXT}
	./${EXT} -v ${TXT}
val2: ${FILE}
	valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all  ./${EXT} ${TXT}

#-fsanitize=address 
#--log-file="valgrind" 