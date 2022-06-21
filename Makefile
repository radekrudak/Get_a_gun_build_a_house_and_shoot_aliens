MAKEFLAGS += --jobs=4
CC = g++
ARGS =  -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17 
OBJ_DIR = obj/
MODE = RELEASE
BACKEND = OLC_PIXEL_GAME_ENGINE

ARGS += -DBACKEND=$(BACKEND)

ifeq ($(MODE),DEBUG)
	ARGS += -g
else 
	ARGS += -O2
endif

default:GAG

dr : debug
	./GAG
d: debug
debug:
		make all MODE=DEBUG -j4

all: clean
	mkdir obj -p
	make --jobs=4
run: all
	./GAG
main.o : src/main.cpp
	$(CC) -o $(OBJ_DIR)$@  $< -c $(ARGS)
OnUserUpdate.o : src/BackEnds/olcPixelGameEngine/OnUserUpdate.cpp
	$(CC) -o $(OBJ_DIR)$@  $< -c $(ARGS)
OnUserCreate.o :src/BackEnds/olcPixelGameEngine/OnUserCreate.cpp
	$(CC) -o $(OBJ_DIR)$@  $< -c $(ARGS)
GetUserInput.o :src/BackEnds/olcPixelGameEngine/GetUserInput.cpp
	$(CC) -o $(OBJ_DIR)$@  $< -c $(ARGS)
GameUpdate.o :src/GameUpdate.cpp
	$(CC) -o $(OBJ_DIR)$@  $< -c $(ARGS)
GameStart.o : src/GameStart.cpp
	$(CC) -o $(OBJ_DIR)$@  $< -c $(ARGS)
GAG: main.o OnUserUpdate.o OnUserCreate.o GetUserInput.o GameUpdate.o GameStart.o
	$(CC) -o $@ $(OBJ_DIR)*.o   $(ARGS)
	make clean
clean:
	-rm -f $(OBJ_DIR)*.o
	-rm -f test
test : src/TEST.cpp
	make clean 
	$(CC) -o $@  $<   $(ARGS)
web:
	em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 ./main.cpp -o ./web_build/pge.html --preload-file ./assets
