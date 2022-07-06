CC = cc
CFLAGS = -g -std=c99 -pedantic -Wall -Werror -Wextra -Wno-deprecated-declarations -fstack-protector-strong -D_POSIX_C_SOURCE=200809L -O2
LIB = 
SRC = time.c sntp.c
OBJ = ${SRC:.c=.o}

%.c:
	${CC} -c ${CFLAGS} $<

time: ${OBJ}
	${CC} -o $@ ${OBJ}

clean:
	rm -f *.o
	rm -f *.gch
	rm -f sntp 

