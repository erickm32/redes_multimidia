#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "jo_jpeg.h"

using namespace std;
int main(){

	int width = 512;
	int height = 512;
	int component = 1;
	int quality = 90;
	char* lena = new char[width*height*component];

	ifstream imagem("lena.raw", ios::binary);
	imagem.read(lena, width*height*component);

	for(int i = 0; i < width; ++i){
		for(int j = 0; j < height; ++j){
			for(int k = 0; k < component; ++k){
				
				//cout << i << " " << j << endl;
				//cout << bitset<8>(lena[i+j+k]) << endl;
			}
		}
	}

	

/*  Basic usage:
 *	char *foo = new char[128*128*4]; // 4 component. RGBX format, where X is unused 
 *	jo_write_jpg("foo.jpg", foo, 128, 128, 4, 90); // comp can be 1, 3, or 4. Lum, RGB, or RGBX respectively.
 */
 	string ret = jo_write_jpg("teste90", lena, width, height, component, quality) ? "ok" : "deu ruim";
 	cout << ret << endl;
 	ret = jo_write_jpg("teste1", lena, width, height, component, 1) ? "ok" : "deu ruim";
	cout << ret << endl;
	ret = jo_write_jpg("teste25", lena, width, height, component, 25) ? "ok" : "deu ruim";
	cout << ret << endl;
	ret = jo_write_jpg("teste75", lena, width, height, component, 75) ? "ok" : "deu ruim";
	cout << ret << endl;
}