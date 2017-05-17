#include "huffman.h"

using namespace std;

Huffman::Huffman(){

}; 

Huffman::~Huffman(){
	if( arquivoProbabilidades.is_open() ){
		arquivoProbabilidades.close();
	}
	if ( arquivoCodificado.is_open() ) {
		arquivoCodificado.close();
	}
	if ( arquivoDecodificado.is_open() ){
		arquivoDecodificado.close();
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
			//arquivoProbabilidades >> linha;
			getline(arquivoProbabilidades, linha);
			if(arquivoProbabilidades.eof()) break;

			if((linha[0] >= 'A' && linha[0] <= 'Z') || linha[0] == ' '){
				char simbolo = linha[0];
				probsLidas[simbolo] = stof(linha.substr(2));
			}
			else{
				arquivoProbabilidades >> linha;
				numeroBytesCodificados = stoi(linha.substr(6));
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


