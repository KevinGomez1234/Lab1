EXECUTABLES=time-4-baby-and-me
SRC=main.c
OBJ=main.o

CC=gcc
CFLAGS=-g -Wall -Wextra

all:$(EXECUTABLES)

$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(EXECUTABLES) $(OBJ) *~ 