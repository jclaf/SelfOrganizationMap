EXEC = my_som
OBJECTS=$(SOURCES: .c=.o)
SOURCES = main.c Som.c Parsing.c nConfig.c -lm
CC=gcc
CFLAGS=-W -Wall -Wextra -Werror -Wconversion -Wpedantic -g -std=gnu99

.PHONY: default clean

default: $(EXEC)

Som.o : Som.c Som.h
Parsing.o: Parsing.c Parsing.h
Vec.o : Vec.h
Bmu.o : Bmu.h
Node.o : Node.h
nConfig.o: nConfig.c nConfig.h
main.o: main.c Som.h Parsing.h Vec.h nConfig.h Bmu.h Node.h 

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.h~) Makefile~
