#include <stdlib.h>

#include "huffman.h"

using namespace std;

int main(){
	string entrada;

	cin >> entrada;

	Huffman *h;

	h = new Huffman(entrada);

	cout << h->getTextoEntrada() << endl;

	return 0;	
}