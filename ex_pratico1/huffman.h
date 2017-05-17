#include <iostream>
#include <fstream>
#include <string>
#include <queue>          // std::priority_queue
#include <map>
#include <stack>
#include <bitset>

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
	stack<int> pbits;
	map<char, string> codigo;
	map<char, int> tamanhoDoCodigo;

	void calculaProbabilidade();
	void geraArvore();
	void printArvore(Nodo *arvore);
	void code(Nodo *raiz);
	void code(Nodo *raiz, const string &codigo);
	char findSymbol(Nodo* raiz, const string& codeReaded);

public:
	Huffman(string textoEntrada, string nomeArquivoProbabilidades, 
		string nomeArquivoCodificado, string nomeArquivoDecodificado);
	~Huffman();
	string getTextoEntrada();
	void comprimeTexto();
	void descomprimeTexto();
};