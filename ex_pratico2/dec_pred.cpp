#include <iostream>

using namespace std;

unsigned char* decodifica(void *data, int width, int height, int comp){
	unsigned char* saida = new unsigned char[width*height*comp];
	unsigned char* residuo = (unsigned char*) data;
	unsigned char* predita = new unsigned char[width*height*comp];

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

					predita[p] = residuo[p];
					//cout << "R: " << (int)residuo[col] << endl;
					//cout << "P: " << (int)predita[p] << endl;
				}
			}
			//predita[x] = residuo[x];
			//cout << "R: " << (int)residuo[x] << endl;

		}
	}

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
					//primeiro elemento
					// if (col == x) {
						// saida[p] =  residuo[p];
					// }
					// else {
						saida[p] = min(255, predita[p] + residuo[p]);
						//if(y < height/512) cout << "S: " << (int)saida[p] << " P: " << (int)predita[p] << " R: " << (int)residuo[p] << endl;
					// }
				}
			}

		}
	}
	free(predita);
	return saida;
}
