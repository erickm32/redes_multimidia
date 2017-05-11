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
	Nodo* arvoreDeProbabilidades;
	priority_queue<Nodo> pq;

	void calculaProbabilidade();
	void geraArvore();
	void printArvore(Nodo *arvore);

public:
	Huffman(string textoEntrada, string nomeArquivoProbabilidades, 
		string nomeArquivoCodificado, string nomeArquivoDecodificado);
	~Huffman();
	string getTextoEntrada();
	void comprimeTexto();
	void descomprimeTexto();
};