CPP = g++-14
CPP_FLAGS ?= -std=c++20
INCLUDE ?= -I../src
LIB_NORODB ?= ../build/lib/norodb.a
LINK ?= -L../build/lib 

all: clean
	$(CPP) $(CPP_FLAGS) $(INCLUDE) -c main.cc 
	$(CPP) $(CPP_FLAGS) -o main main.o $(LINK) $(LIB_NORODB) 
	./main

clean:
	rm -rf norodb || true
	rm -rf *.o || true
