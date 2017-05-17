#include <iostream>

#include "jo_jpeg.cpp"

int main(){

	//jo_write_jpg(const char *filename, const void *data, int width, int height, int comp, int quality);
	int width = 512;
	int height = 512;
	int components = 1;
	int quality = 90;
	char* lena = new char[width*height*components];

	for(int i = 0; i < width; i++){
		for(int j = 0; i < height; ++j){

		}
	}


	jo_write_jpg("teste", lena, width, height, components, quality);
}