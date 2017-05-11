#include <iostream>
#include <fstream>
#include <string>
#include <queue>          // std::priority_queue
#include <map>

#include "nodo.h"

using namespace std;

class Huffman {
private:
	string textoEntrada;
	
	string nomeArquivoProbabilidades;
	string nomeArquivoCodificado;
	string nomeArquivoDecodificado;

	fstream arquivoProbabilidades, arquivoCodificado, arquivoDecodificado;

	int qntCaracteresEntrada;
	map<char,float> hash_caracteres;

public:
	Huffman(string textoEntrada, string nomeArquivoProbabilidades, 
		string nomeArquivoCodificado, string nomeArquivoDecodificado);
	~Huffman();
	string getTextoEntrada();
	void calculaProbabilidade();
	void geraArvore();
	void comprimeTexto();
	void descomprimeTexto();
};