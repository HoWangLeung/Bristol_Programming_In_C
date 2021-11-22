CC=clang
CFLAGS=-Wall -Wextra  -pedantic -std=c99  -O3  
SANITIZE= -fsanitize=undefined -fsanitize=address 
LDLIBS=-lm
FILE=func_b1
FILE2=main_b1


all: ${FILE} 
${FILE}: ${FILE}.c ${FILE2}.c
	$(CC) ${FILE}.c ${FILE2}.c -o ${FILE} ${CFLAGS} ${SANITIZE} ${LDLIBS} 
val: ${FILE}
	valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all  ./${FILE}
r: ${FILE}
	./${FILE}


#-fsanitize=address 
#--log-file="valgrind" 