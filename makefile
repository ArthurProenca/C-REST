PROJ_NAME=rest_operations
C_SOURCE=$(wildcard *.c)
H_SOURCE=$(wildcard *.h)
OBJ=$(C_SOURCE:.c=.o)
CC=gcc
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -pedantic 	\
		 -lssl -lcrypto

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(CC_FLAGS)

%.o: %.c $(H_SOURCE)
	$(CC) $< -o $@ $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME)

run:
	gcc -o main rest_operations.o http_methods.o -lssl -lcrypto