#include <stdlib.h>

#include "huffman.h"

using namespace std;

int main(){
	string nomeArquivoEntrada = "entrada2.txt";

	string nomeArquivoProbabilidades = "probs.txt";
	string nomeArquivoCodificado = "coded.bin";
	string nomeArquivoDecodificado = "saida.txt";

	Huffman *h;

	h = new Huffman();

	h->comprimeTexto(nomeArquivoEntrada, nomeArquivoProbabilidades, nomeArquivoCodificado);
	h->descomprimeTexto(nomeArquivoProbabilidades, nomeArquivoCodificado, nomeArquivoDecodificado);

	delete h;

	return 0;	
}