#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "jo_jpeg.h"

unsigned char* codifica(void *data, int width, int height, int comp);
unsigned char* decodifica(void *data, int width, int height, int comp);

using namespace std;

int main(){

	int width = 512, height = 512, component = 1, quality = 90;
	unsigned char* original = new unsigned char[width*height*component];

	// abre o raw da imagem original
	ifstream imagem("lena.raw", ios::binary);
	imagem.read((char*)original, width*height*component);
	imagem.close();

	// aplica a predição sobre a 'original' e retorna o residuo, 'original' - 'predita'
	unsigned char* residuo = codifica((void*)original, width, height, component);

	if (residuo != NULL){
		cout << "Residuo ok" << endl;
	}
	else{
		cout << "Algo de errado não está certo na predição." << endl;
		exit(1);
	}

	// guarda o residuo em um .raw
	ofstream saida("residuo.raw", ios::binary);
	saida.write((char*)residuo, width*height*component);
	saida.close();

	// faz um jpg da imagem original e da de residuo, mais para teste e visualização
	string ret = jo_write_jpg("original-90.jpg", original, width, height, component, quality) ? "ok" : "deu ruim";
	cout << "Original: " << ret << endl;
	ret = jo_write_jpg("residuo-90.jpg", residuo, width, height, component, quality) ? "ok" : "deu ruim";
	cout << "Residuo: " << ret << endl;
	free(residuo);
	free(original);
	// acaba a etapa de predição

	//começa a etapa inversa, "despredição"

	//le o arquivo com informação de predição
	residuo = new unsigned char[width*height*component];
	ifstream predita_raw("residuo.raw", ios::binary);
	predita_raw.read((char*)residuo, width*height*component);
	predita_raw.close();

	unsigned char *reconstruida = decodifica((void*)residuo, width, height, component);

	if(reconstruida != NULL){
		cout << "reconstruida: ok" << endl;
	}
	else{
		cout << "Problema na hora da reconstrução da imagem." << endl;
	}

	// faz um jpg da imagem original reconstruida, mas não ficou bem correta
	ret = jo_write_jpg("original-reconstruida-90.jpg", reconstruida, width, height, component, quality) ? "ok" : "deu ruim";
	cout << "Original reconstruida: " << ret << endl;

	free(residuo);
	free(reconstruida);
	return 0;
}
