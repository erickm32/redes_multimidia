#include <stdlib.h>

#include "huffman.h"

using namespace std;

int main(){
	string entrada;
	string arquivoProbabilidades = "probs.txt";
	string arquivoCodificado = "coded";
	string arquivoDecodificado = "saida.txt";

	cin >> entrada;

	Huffman *h;

	h = new Huffman(entrada, arquivoProbabilidades, arquivoCodificado, arquivoDecodificado);

	//cout << h->getTextoEntrada() << endl;
	//Foram gerados 5 parágrafos 520 palavrase 3472 bytes de LoremIpsum

	h->calculaProbabilidade();

	return 0;	
}