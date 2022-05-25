#default:
#	g++ -o GAG main.cpp  OnUserUpdate.cpp -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
ARGS = -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
all: GAG 

main.o : main.cpp
	g++ -o $@  $< -c $(ARGS)
OnUserUpdate.o : OnUserUpdate.cpp
	g++ -o $@  $< -c $(ARGS)
OnUserCreate.o :OnUserCreate.cpp 
	g++ -o $@  $< -c $(ARGS)
GAG: main.o OnUserUpdate.o OnUserCreate.o 
	g++ -o $@ $?   $(ARGS)
clean:
	touch GAG
	rm GAG
	rm *.o
	