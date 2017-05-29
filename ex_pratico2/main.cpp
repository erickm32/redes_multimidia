#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "jo_jpeg.h"

bool codifica(const char *filename, void *data, int width, int height, int comp, int quality);
bool decodifica(const char *filename, void *data, int width, int height, int comp, int quality);
// ???

using namespace std;

int main(){

	int width = 512;
	int height = 512;
	int component = 1;
	int quality = 90;
	unsigned char* lena = new unsigned char[width*height*component];

	ifstream imagem("lena.raw", ios::binary);
	imagem.read((char*)lena, width*height*component);
	//lena, menor byte 91, maior byte 221

	bool cod = codifica("deixaQuietoPorAgora", lena, width, height, component, quality);
	string ret = jo_write_jpg("testandoMexerNoRaw90", lena, width, height, component, quality) ? "ok" : "deu ruim";
 	cout << ret << endl;

	if (cod){
		cout << "Codificou ok" << endl;
	}
	else{
		cout << "Algo de errado não está certo na codificação." << endl;
	}

/*
	bool decod = decodifica("deixaQuietoPorAgora", lena, width, height, component, quality);

	if (decod){
		cout << "Decodificou ok" << endl;
	}
	else{
		cout << "Algo de errado não está certo na codificação." << endl;
	}
*/

	

/*  Basic usage:
 *	char *foo = new char[128*128*4]; // 4 component. RGBX format, where X is unused 
 *	jo_write_jpg("foo.jpg", foo, 128, 128, 4, 90); // comp can be 1, 3, or 4. Lum, RGB, or RGBX respectively.
 
 	string ret = jo_write_jpg("teste90", lena, width, height, component, quality) ? "ok" : "deu ruim";
 	cout << ret << endl;
 	ret = jo_write_jpg("teste1", lena, width, height, component, 1) ? "ok" : "deu ruim";
	cout << ret << endl;
	ret = jo_write_jpg("teste25", lena, width, height, component, 25) ? "ok" : "deu ruim";
	cout << ret << endl;
	ret = jo_write_jpg("teste75", lena, width, height, component, 75) ? "ok" : "deu ruim";
	cout << ret << endl;
 */
	return 0;
}