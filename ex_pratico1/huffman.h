#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

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
	map<char, string> codigo;
	map<char, int> tamanhoDoCodigo;

	int numeroBytesCodificados;

	void calculaProbabilidade();
	void geraArvore();
	void code(Nodo *raiz, const string &codigo);
	map<char, float> probsParser();
	char findSymbol(Nodo* raiz, const string& codeReaded);

public:
	Huffman();
	~Huffman();
	void comprimeTexto( string textoEntrada, 
						string nomeArquivoProbabilidades, 
						string nomeArquivoCodificado);
	void descomprimeTexto(	string nomeArquivoProbabilidades, 
							string nomeArquivoCodificado, 
							string nomeArquivoDecodificado);
};