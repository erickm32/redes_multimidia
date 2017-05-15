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
	Nodo *esquerda,*direita, *novo;
	while(pq.size() > 1){
		//cout << "size: " << pq.size() << " pq: " << "'" << pq.top().simbolo << "' => " << pq.top().probabilidade << endl;
		direita = new Nodo(pq.top()); pq.pop();
		esquerda = new Nodo(pq.top()); pq.pop();
		//cout << "esquerda " << esquerda->probabilidade << " direita " << direita->probabilidade  << endl;
		novo = new Nodo(esquerda, direita, NULL, esquerda->probabilidade + direita->probabilidade, '\0');
		direita->raiz = novo;
		esquerda->raiz = novo;

		//cout << "novo " << novo->simbolo << " " << novo->probabilidade <<
		// 	" esq: " << novo->filhoEsquerda->probabilidade << " dir: " << novo->filhoDireita->probabilidade << endl;
		pq.push(*novo);
	}
	cout << "geraArvore\n" ;
	cout << pq.top().simbolo << " " << pq.top().probabilidade << endl;
	arvoreDeProbabilidades = new Nodo(pq.top());
	
	printArvore(arvoreDeProbabilidades);
}; 

void Huffman::printArvore(Nodo* arvore){
	if(arvore != NULL){
		printArvore(arvore->filhoEsquerda);
		//if(arvore->simbolo != '\0')
			cout << "'" << arvore->simbolo << "' " << arvore->probabilidade << endl;
		printArvore(arvore->filhoDireita);
	}
}


	int codigo_calc = 0;
 	int comprimento = 0;
void Huffman::code(Nodo *raiz){
	//cout << "Chega no inicio\n";
	if (raiz != NULL){
		pbits.push(0);  		//push(pbits, 0);
		cout << "antes esquerda raiz->simbolo " << raiz->simbolo << " " << raiz->probabilidade << " " << pbits.size() << endl;
	 	code(raiz->filhoEsquerda);
	 	pbits.pop(); 			//pop(pbits);
	 	pbits.push(1); 		//push(pbits, 1);
	 	cout << "antes direita raiz->simbolo " << raiz->simbolo << " " << raiz->probabilidade << " " << pbits.size() << endl;
	 	code(raiz->filhoDireita);
	 	pbits.pop(); 			//pop(pbits);
 	}
 	else{ //chegou na folha
 		//cout << "Chega em una folha";
 		if(!pbits.empty()){ cout << "pbits.size: " << pbits.size() << endl;}
 		stack<int> pilha_codigo = pbits; //copia a pilha inteira
 		codigo_calc = 0;
 		comprimento = 0;
 		while (!pilha_codigo.empty()){
 			codigo_calc = codigo_calc | pilha_codigo.top(); //ou bit-a-bit
 			codigo_calc = codigo_calc << 1;
 			//cout << "codigo_calc " << codigo_calc << " top: " << pilha_codigo.top();
 			pilha_codigo.pop();
 			comprimento += 1;
 			//cout << " comprimento " << comprimento << endl; 
 		}
 	}
 	if(raiz != NULL){
 		if(raiz->simbolo != '\0'){
 			tamanhoDoCodigo[raiz->simbolo] = comprimento;
 			codigo[raiz->simbolo] = codigo_calc;
 		}
 	}
}

void Huffman::comprimeTexto(){
	calculaProbabilidade();
	geraArvore();
	code(arvoreDeProbabilidades);

	for(map<char,int>::iterator it=codigo.begin(); it!=codigo.end(); ++it){
		cout << "char: " << it->first << " codigo " << bitset<12>( it->second )
			 << dec << " tamanhoDoCodigo " << tamanhoDoCodigo[it->first] << endl;
	}




	arquivoCodificado.open(nomeArquivoCodificado.data(), ios::out | ios::binary );
	if ( arquivoCodificado.is_open() ){

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
