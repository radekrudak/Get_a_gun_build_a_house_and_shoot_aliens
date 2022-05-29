MAKEFLAGS += --jobs=4

ARGS = -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
OBJ_DIR = obj/

default: GAG

all: clean
	make --jobs=4
run: all
	./GAG
main.o : src/main.cpp
	g++ -o $(OBJ_DIR)$@  $< -c $(ARGS)
OnUserUpdate.o : src/OnUserUpdate.cpp
	g++ -o $(OBJ_DIR)$@  $< -c $(ARGS)
OnUserCreate.o :src/OnUserCreate.cpp 
	g++ -o $(OBJ_DIR)$@  $< -c $(ARGS)
GetUserInput.o :src/GetUserInput.cpp
	g++ -o $(OBJ_DIR)$@  $< -c $(ARGS)

GAG: main.o OnUserUpdate.o OnUserCreate.o GetUserInput.o
	g++ -o $@ $(OBJ_DIR)*.o   $(ARGS)
	make clean
clean:
	-rm -f $(OBJ_DIR)*.o
	-rm -f test
test : TEST.cpp
	make clean 
	g++ -o $@  $<   $(ARGS)
