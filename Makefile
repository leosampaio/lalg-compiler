CXX=g++
CC=gcc
LEX=lex
CFLAGS= -O2
CXXFLAGS= -O2
LIBS= -ll

OBJ= build/lex.yy.o build/lalg.o

all:
	@make clean
	@make main

main: $(OBJ)
	$(CXX) -o lalg $(CXXFLAGS) $^ $(LIBS)

run:
	./lalg

# compile only, C source
build/lex.yy.o: lalg.l lex.yy.c
	@mkdir -p build
	$(LEX) lalg.l
	$(CC) -c -o build/lex.yy.o lex.yy.c $(CFLAGS)

lex.yy.c:
	$(LEX) lalg.l

# compile only, C++ source
build/%.o: %.cpp
	@mkdir -p build
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	@rm -f $(OBJ)