CC=clang
CFLAGS=-Wall -Wextra  -pedantic -std=c99  -g3  
SANITIZE= -fsanitize=undefined -fsanitize=address 
LDLIBS=-lm
FILE=test



all: ${FILE}
${FILE}: ${FILE}.c
	$(CC) ${FILE}.c -o ${FILE} ${CFLAGS} ${SANITIZE} ${LDLIBS}
val: ${FILE}
	valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all  ./${FILE} 
r: ${FILE}
	./${FILE} 
v: ${FILE}
	./${FILE}


#-fsanitize=address 
#--log-file="valgrind" 