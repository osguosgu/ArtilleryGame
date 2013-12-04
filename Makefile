SFML=./SFML-2.1
CC=g++
CFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic -I $(SFML)/include
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L $(SFML)/lib -Wl,-rpath=$(SFML)/lib -Wl,-rpath-link=$(SFML)/lib

SOURCES=game.cc terrain.cc basicCannon.cc
OBJECTS=game.o terrain.o basicCannon.o

EXECUTABLE=game

all: $(SOURCES) $(EXECUTABLE)
  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
