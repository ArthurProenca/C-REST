CC=gcc
#CCFLAGS=-Wall
CCFLAGS=-g
LDFLAGS=-lm
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=rest_operations

all: $(TARGET)

$(TARGET): $(OBJECTS);\
    $(CC) -g -o $@ $^ $(LDFLAGS) -lssl -lcrypto

%.o: %.c %.h;\
    $(CC) $(CCFLAGS) -lssl -lcrypto -c $<

%.o: %.c;\
    $(CC) $(CCFLAGS) -lssl -lcrypto -c $<

clean:;\
    rm -f *.o $(TARGET);\