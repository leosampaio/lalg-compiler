CXX=g++
LEX=lex
CFLAGS= -ll
CXXFLAGS=-g -ll

OBJ= build/lex.yy.o build/lalg.o

all: $(OBJ)
	$(LEX) lalg.l
	$(CXX) -o lalg $(CXXFLAGS) $^

# compile only, C source
build/%.o: %.c
	@mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

# compile only, C++ source
build/%.o: %.cpp
	@mkdir -p build
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	@rm -f $(OBJ)