#include <iostream>
#include <string>
#include <queue>          // std::priority_queue

using namespace std;

class Huffman {
private:
	std::string textoEntrada;
	int qntCaracteresEntrada;
public:
	Huffman(string textoEntrada);
	string getTextoEntrada();
	void calculaProbabilidade();
	void comprimeTexto();
	void descomprimeTexto();
};