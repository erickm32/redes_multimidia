CC=g++
FLAGS=-Wall -std=c++11
all: main.cpp jo_jpeg.cpp
	 $(CC) -o pred main.cpp jo_jpeg.cpp $(FLAGS)

debug: main.cpp 
	$(CC) -g main.cpp main.cpp $(FLAGS)
	
clean:
	rm -rf *.o pred 
 