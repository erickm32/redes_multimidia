CC=g++
FLAGS=-Wall -std=c++11
all: main.cpp jo_jpeg.cpp
	 $(CC) -o pred main.cpp jo_jpeg.cpp $(FLAGS)

debug: huffman.cpp main.cpp
	$(CC) -g huffman.cpp main.cpp $(FLAGS)
	
clean:
	rm -rf *.o huffman coded probs.txt
 