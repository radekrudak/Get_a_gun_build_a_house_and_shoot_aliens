#default:
#	g++ -o GAG main.cpp  OnUserUpdate.cpp -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
all: GAG
	
# OnUserCreate.o : OnUserCreate.cpp
# 		g++ -o $@ $? -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
# OnUserUpdate.o : OnUserUpdate.cpp
# 		g++ -o $@  $? -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
# main.o : main.cpp
# 		g++ -o $@  $? -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
GAG: main.cpp OnUserUpdate.cpp OnUserCreate.cpp
	g++ -o $@  main.cpp OnUserUpdate.cpp OnUserCreate.cpp -g -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17