###################################
# CS 433 - Programming Assignment 2
# Keith Adams and Jason Meyer
# 
###################################
CC = g++
CFLAGS = -Wall
#LIB = -lm
#LDFLAGS = -L.
PROG = main
OBJ = main.o UNIX_shell.o 
SRC = main.cpp UNIX_shell.cpp 

all : $(PROG)

$(PROG): $(OBJ) 
	$(CC) -c $(CFLAGS) $(SRC)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)


# cleanup
clean:
	/bin/rm -f *.o $(PROG)

# DO NOT DELETE
