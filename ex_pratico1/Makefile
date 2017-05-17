CC=g++
FLAGS=-Wall -std=c++11
all: huffman.cpp main.cpp
	 $(CC) -o huffman huffman.cpp comprimir.cpp descomprimir.cpp main.cpp $(FLAGS)

debug: huffman.cpp main.cpp
	$(CC) -g huffman.cpp main.cpp $(FLAGS)
	
clean:
	rm -rf *.o huffman coded probs.txt
 