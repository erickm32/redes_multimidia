#include <stdlib.h>

#include "huffman.h"

using namespace std;

int main(){
	string entrada;
	string arquivoProbabilidades = "probs.txt";
	string arquivoCodificado = "coded.bin";
	string arquivoDecodificado = "saida.txt";

	getline(cin, entrada);

	Huffman *h;

	h = new Huffman(entrada, arquivoProbabilidades, arquivoCodificado, arquivoDecodificado);

	//cout << h->getTextoEntrada() << endl;

	h->comprimeTexto();
	h->descomprimeTexto();

	delete h;

	return 0;	
}