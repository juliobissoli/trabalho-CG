CC		:= g++
CFLAGS	:= 

BIN		:= bin
SRC		:= src
INCLUDE	:= include

PROGARGS	:= 

EXECUTABLE	:= trabalhocg
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)

VALGRIND	:= 

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.cpp=.o)

all: clean $(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(EXECUTABLE)
	-$(RM) $(OBJECTS)


run: all
	./$(EXECUTABLE) < input/input1.txt

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES) -std=c++17 -lm -g -lGL -lGLU -lglut -Wall -pedantic -Wextra -Wno-unused-parameter -Wwrite-strings

val: all
	valgrind ./$(EXECUTABLE) < input/input1.txt

full: all
	- valgrind -v --leak-check=full ./$(EXECUTABLE) $(PROGARGS)
