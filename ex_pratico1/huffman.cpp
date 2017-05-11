#include "huffman.h"

using namespace std;

Huffman::Huffman(string textoEntrada, string nomeArquivoProbabilidades, 
	string nomeArquivoCodificado, string nomeArquivoDecodificado){

	this->textoEntrada = textoEntrada;
	this->qntCaracteresEntrada = textoEntrada.size();
	this->nomeArquivoProbabilidades = nomeArquivoProbabilidades;
	this->nomeArquivoCodificado = nomeArquivoCodificado;
	this->nomeArquivoDecodificado = nomeArquivoDecodificado;

	this->arvoreDeProbabilidades = NULL;
	
}; 

Huffman::~Huffman(){
	if( arquivoProbabilidades.is_open() ){
		arquivoProbabilidades.close();
	}
	if ( arquivoCodificado.is_open() ) {
		arquivoCodificado.close();
	}
}

void Huffman::calculaProbabilidade(){
	for(int i = 0; i < qntCaracteresEntrada; ++i){
		hash_caracteres[textoEntrada[i]]++;
	}

	for (map<char,float>::iterator it=hash_caracteres.begin(); it!=hash_caracteres.end(); ++it){
		it->second = it->second / qntCaracteresEntrada;
    	//cout << it->first << " => " << it->second << '\n';
	}

	arquivoProbabilidades.open(nomeArquivoProbabilidades.data(), ios::out);// | ios::app);
	if ( arquivoProbabilidades.is_open() ){
		// Grava no arquivo de probabilidades e faz a fila de prioridades
		for (map<char,float>::iterator it=hash_caracteres.begin(); it!=hash_caracteres.end(); ++it){
			Nodo *nodo = new Nodo(NULL, NULL, NULL, it->second, it->first);
			pq.push(*nodo);
    		delete nodo;
    		arquivoProbabilidades << it->first << " " << it->second << '\n';
		}
		arquivoProbabilidades.close();
	}
	else{
		cerr << "Não foi possível gravar o arquivo de probabilidades" << endl;
	}
};

void Huffman::geraArvore(){

	while(pq.size() > 0){
		cout << "size: " << pq.size() << " pq: " << "'" << pq.top().simbolo << "' => " << pq.top().probabilidade << endl;
		pq.pop();
	}


}; 

void Huffman::comprimeTexto(){
	arquivoCodificado.open(nomeArquivoCodificado.data(), ios::out | ios::binary );
	if ( arquivoCodificado.is_open() ){
		calculaProbabilidade();
		geraArvore();


		arquivoCodificado.close();
	}
	else {
		cerr << "Não foi possível gravar o arquivo codificado" << endl;
	}
};

void Huffman::descomprimeTexto(){
	arquivoCodificado.open(nomeArquivoCodificado.data(), ios::in | ios::binary );
	arquivoProbabilidades.open(nomeArquivoProbabilidades.data(), ios::in );
	arquivoDecodificado.open(nomeArquivoDecodificado.data(), ios::out);

	if ( !arquivoCodificado.is_open() ){
		cerr << "Não foi possível ler o arquivo codificado" << endl;
	}
	if ( !arquivoProbabilidades.is_open() ){
		cerr << "Não foi possível ler o arquivo de probabilidades" << endl;
	}
	if ( !arquivoDecodificado.is_open() ){
		cerr << "Não foi possível ler o arquivo codificado" << endl;
	}


	arquivoDecodificado.close();
	arquivoProbabilidades.close();
	arquivoCodificado.close();

};

string Huffman::getTextoEntrada(){
	return textoEntrada;
}
