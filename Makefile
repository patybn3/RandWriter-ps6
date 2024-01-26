CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = RandWriter.hpp
# Your compiled .o files
OBJECTS = RandWriter.o
# The name of your program
PROGRAM = TextWriter
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) TextWriter.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): TextWriter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

TextWriter.a: $(OBJECTS)
	ar rcs TextWriter.a $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(TEST) TextWriter.a

lint:
	cpplint *.cpp *.hpp