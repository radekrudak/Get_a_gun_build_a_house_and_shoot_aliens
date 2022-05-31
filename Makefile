MAKEFLAGS += --jobs=4

ARGS =  -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
OBJ_DIR = obj/
MODE = RELEASE

ifeq ($(MODE),DEBUG)
	ARGS += -g
else 
	ARGS += -O2
endif

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
web:
	em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 ./main.cpp -o ./web_build/pge.html --preload-file ./assets
