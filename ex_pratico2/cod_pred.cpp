#include <iostream>

using namespace std;

unsigned char* codifica(void *data, int width, int height, int comp){
	unsigned char *predita = new unsigned char[width*height*comp];
	unsigned char *original = (unsigned char*) data;

	// achei mais apropriado utilizar a forma que o autor do codificador jpeg
	// passado faz para percorrer os dados
	// Encode 8x8 macroblocks
	for(int y = 0; y < height; y += 8) {
		for(int x = 0; x < width; x += 8) {
			//começa a percorrer um bloco 8x8
			for(int row = y; row < y+8; ++row) {
				for(int col = x; col < x+8; ++col) {
					int p = row*width*comp + col*comp;
					if(row >= height) {
						p -= width*comp*(row+1 - height);
					}
					if(col >= width) {
						p -= comp*(col+1 - width);
					}
					// Repete a informação da primeira coluna em todo o bloco
					predita[p] = original[x];
				}
			}
			//
		}
	}

	unsigned char* residuo = new unsigned char[width*height*comp];

	for(int y = 0; y < height; y += 8) {
		for(int x = 0; x < width; x += 8) {

			for(int row = y; row < y+8; ++row) {
				for(int col = x; col < x+8; ++col) {
					int p = row*width*comp + col*comp;
					if(row >= height) {
						p -= width*comp*(row+1 - height);
					}
					if(col >= width) {
						p -= comp*(col+1 - width);
					}
					//residuo[p] = original[p] > predita[p] ? original[p] - predita[p] : predita[p] - original[p];
					//residuo[p] = original[p] - predita[p];
					residuo[p] = max(0, original[p] - predita[p]);
				}
			}
		}
	}
	free(predita);
	return residuo;
}
