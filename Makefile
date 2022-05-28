MAKEFLAGS += --jobs=4

ARGS = -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
default: GAG

all: clean
	make --jobs=4
run: all
	./GAG
main.o : main.cpp
	g++ -o $@  $< -c $(ARGS)
OnUserUpdate.o : OnUserUpdate.cpp
	g++ -o $@  $< -c $(ARGS)
OnUserCreate.o :OnUserCreate.cpp 
	g++ -o $@  $< -c $(ARGS)
GAG: main.o OnUserUpdate.o OnUserCreate.o 
	g++ -o $@ $?   $(ARGS)
clean:
	-rm -f GAG
	-rm -f *.o
	