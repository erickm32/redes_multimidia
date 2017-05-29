#include <iostream>

using namespace std;

bool codifica(const char *filename, void *data, int width, int height, int comp, int quality){
	unsigned char *imagem = (unsigned char*)data;
	// Encode 8x8 macroblocks
	const unsigned char *imageData = (const unsigned char *)data;
	int ofsG = comp > 1 ? 1 : 0, ofsB = comp > 1 ? 2 : 0;
	for(int y = 0; y < height; y += 8) {
		for(int x = 0; x < width; x += 8) {
			float primeiraLinha[8] = {0}, primeiraColuna[8] = {0};
			for(int row = y, i = 0; row < y+8; ++row, ++i) { // , pos = 0
				for(int col = x, j = 0; col < x+8; ++col, ++j) { // , ++pos
					int p = row*width*comp + col*comp;
					if(row >= height) {
						p -= width*comp*(row+1 - height);
					}
					if(col >= width) {
						p -= comp*(col+1 - width);
					}
					if(col == x){ // primeiro indice a ser visto
						primeiraColuna[i] = imagem[p+0];
					}
					if(row == y){ // primeiro indice tambem
						primeiraLinha[j] = imagem[p+0];
					}

					//float r = imageData[p+0], g = imageData[p+ofsG], b = imageData[p+ofsB];
					// nao importam por ser somente preto e branco

					float v = imageData[p+0];
					cout << "V: " << v << endl;
					imagem[p+0]+=20;
					//imagem[p+ofsG]+=20;
					//imagem[p+ofsB]+=20;
					//cout << p << " " << ofsG << " " << ofsB << endl;

					
					/*
					YDU[pos]=+0.29900f*r+0.58700f*g+0.11400f*b-128;
					UDU[pos]=-0.16874f*r-0.33126f*g+0.50000f*b;
					VDU[pos]=+0.50000f*r-0.41869f*g-0.08131f*b;
					*/
				}
				cout << "Linha?" << endl;
			}
			cout << "Bloco?" << endl;
			for(int i = 0; i < 8; ++i){
				cout << "primeiraColuna[" << i << "]: " << primeiraColuna[i] << endl;
			}
			for (int j = 0; j < 8; ++j){
				cout << "primeiraLinha[" << j << "]: " << primeiraLinha[j] << endl;
			}
		}
	}
	
	return true;
}