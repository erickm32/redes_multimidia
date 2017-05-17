#include "huffman.h"

using namespace std;

Huffman::Huffman(string textoEntrada, string nomeArquivoProbabilidades, 
	string nomeArquivoCodificado, string nomeArquivoDecodificado){

	this->textoEntrada = textoEntrada;
	this->qntCaracteresEntrada = textoEntrada.size();
	this->nomeArquivoProbabilidades = nomeArquivoProbabilidades;
	this->nomeArquivoCodificado = nomeArquivoCodificado;
	this->nomeArquivoDecodificado = nomeArquivoDecodificado;	
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
	}

	arquivoProbabilidades.open(nomeArquivoProbabilidades.data(), ios::out);// | ios::app);
	if ( arquivoProbabilidades.is_open() ){
		// Grava no arquivo de probabilidades e faz a fila de prioridades
		for (map<char,float>::iterator it=hash_caracteres.begin(); it!=hash_caracteres.end(); ++it){
			Nodo *nodo = new Nodo(NULL, NULL, NULL, it->second, it->first);
			pq.push(*nodo);
    		delete nodo;
    		arquivoProbabilidades << it->first << " " << fixed << std::setfill('0') << std::setprecision(30) <<  it->second << '\n';
		}
		arquivoProbabilidades << "bytes " << qntCaracteresEntrada << endl;
		arquivoProbabilidades.close();
	}
	else{
		cerr << "Não foi possível gravar o arquivo de probabilidades" << endl;
	}
};

void Huffman::geraArvore(){
	Nodo *esquerda,*direita, *novo;
	while(pq.size() > 1){
		direita = new Nodo(pq.top()); pq.pop();
		esquerda = new Nodo(pq.top()); pq.pop();
		novo = new Nodo(esquerda, direita, NULL, esquerda->probabilidade + direita->probabilidade, '\0');
		direita->raiz = novo;
		esquerda->raiz = novo;

		pq.push(*novo);
	}

	arvoreDeProbabilidades = new Nodo(pq.top());
	while(!pq.empty()){
		pq.pop();
	}
}; 


void Huffman::code(Nodo *raiz, const string &codigo){
	if (raiz != NULL){
		raiz->codigo = codigo + '1';
	 	code(raiz->filhoEsquerda, raiz->codigo);
	 	raiz->codigo.pop_back();
	 	raiz->codigo = codigo + '0';
	 	code(raiz->filhoDireita, raiz->codigo);
	 	raiz->codigo.pop_back();
	 	if(raiz->simbolo != '\0'){
 			tamanhoDoCodigo[raiz->simbolo] = codigo.size();
 			this->codigo[raiz->simbolo] = codigo;
 		}
 	}
}

map<char, float> Huffman::probsParser(){
	if(!arquivoProbabilidades.is_open()){
		arquivoProbabilidades.open(nomeArquivoProbabilidades, ios::in);
	}
	map<char, float> probsLidas;
	if(arquivoProbabilidades.is_open()){
		string linha;
		while(!arquivoProbabilidades.eof()){
			arquivoProbabilidades >> linha;
			if(arquivoProbabilidades.eof()) break;

			try{
				float probabilidadeEspaco = stof(linha);
				probsLidas[' '] = probabilidadeEspaco;

			} catch (invalid_argument& e){
				if(linha == "bytes"){
					arquivoProbabilidades >> linha;
					numeroBytesCodificados = stoi(linha);
				}
				if((linha[0] >= 'A' && linha[0] <= 'Z') || linha[0] == ' '){
					char c = linha[0];
					arquivoProbabilidades  >> linha;
					probsLidas[c] = stof(linha);
				}
			}
		}
	}
	else{
		cerr << "Erro ao ler o arquivo de probabilidades" << endl;
	}
	arquivoProbabilidades.close();
	return probsLidas;
};


char Huffman::findSymbol(Nodo* raiz, const string& codeReaded){
	if(raiz != NULL){
		if (raiz->codigo == codeReaded){
			return raiz->simbolo;
		}
		else{
			char ret;
			ret = findSymbol(raiz->filhoEsquerda, codeReaded);
			if(ret == '\0'){
				ret = findSymbol(raiz->filhoDireita, codeReaded);
			}
			return ret;
		}
	}
	return '\0';
}


