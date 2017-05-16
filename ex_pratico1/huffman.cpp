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
		//cout << "_" << endl;
		//cout << "size: " << pq.size() << " pq: " << "'" << pq.top().simbolo << "' => " << pq.top().probabilidade << endl;
		//cout << pq.top().simbolo << " " << pq.top().probabilidade << " " << pq.top().probabilidade * qntCaracteresEntrada << endl;
		direita = new Nodo(pq.top()); pq.pop();
		//cout << pq.top().simbolo << " " << pq.top().probabilidade << " " << pq.top().probabilidade * qntCaracteresEntrada << endl;
		esquerda = new Nodo(pq.top()); pq.pop();
		novo = new Nodo(esquerda, direita, NULL, esquerda->probabilidade + direita->probabilidade, '\0');
		direita->raiz = novo;
		esquerda->raiz = novo;
		//cout << "n" << novo->simbolo << " " << novo->probabilidade << " " << novo->probabilidade * qntCaracteresEntrada << endl;

		//cout << "novo " << novo->simbolo << " " << novo->probabilidade <<
		// 	" esq: " << novo->filhoEsquerda->probabilidade << " dir: " << novo->filhoDireita->probabilidade << endl;
		pq.push(*novo);
		//cout << "-" << endl;
	}
	//cout << "geraArvore\n" ;
	//cout << pq.top().simbolo << " " << pq.top().probabilidade << endl;
	arvoreDeProbabilidades = new Nodo(pq.top());
	
	//printArvore(arvoreDeProbabilidades);
}; 

void Huffman::printArvore(Nodo* arvore){
	if(arvore != NULL){
		printArvore(arvore->filhoEsquerda);
		//if(arvore->simbolo != '\0')
			cout << "'" << arvore->simbolo << "' " << arvore->probabilidade << endl;
		printArvore(arvore->filhoDireita);
	}
}


void printCod(Nodo* arvore){
	if(arvore != NULL){
		printCod(arvore->filhoEsquerda);
		if(arvore->simbolo != '\0')
			cout << "'" << arvore->simbolo << "' " << arvore->probabilidade << " _" << arvore->codigo << "_" << endl;
		printCod(arvore->filhoDireita);
	}
}


	int codigo_calc = 0;
 	int comprimento = 0;
void Huffman::code(Nodo *raiz, const string &codigo){
	//cout << "Chega no inicio\n";
	if (raiz != NULL){
		pbits.push(1);  		//push(pbits, 0);
		raiz->codigo = codigo + '1';
	 	code(raiz->filhoEsquerda, raiz->codigo);
	 	raiz->codigo.pop_back();
	 	pbits.pop(); 			//pop(pbits);
	 	pbits.push(0); 		//push(pbits, 1);
	 	raiz->codigo = codigo + '0';
	 	code(raiz->filhoDireita, raiz->codigo);
	 	raiz->codigo.pop_back();
	 	pbits.pop(); 			//pop(pbits);
	 	if(raiz->simbolo != '\0'){
 			//tamanhoDoCodigo[raiz->simbolo] = comprimento;
 			tamanhoDoCodigo[raiz->simbolo] = codigo.size();
 			//this->codigo[raiz->simbolo] = codigo_calc;
 			this->codigo[raiz->simbolo] = codigo;
 		}
 	}
 	else{ //chegou na folha
 		stack<int> pilha_codigo = pbits; //copia a pilha inteira
 		codigo_calc = 0;
 		comprimento = 0;
 		while (!pilha_codigo.empty()){
 			codigo_calc = codigo_calc | pilha_codigo.top(); //ou bit-a-bit
 			codigo_calc = codigo_calc << 1;
 			pilha_codigo.pop();
 			comprimento += 1;
 		}
 	}
}

int current_bit = 0;
unsigned char bit_buffer;

FILE *f;

void WriteBit (int bit){
  if (bit)
    bit_buffer |= (1<<current_bit);

  current_bit++;
  if (current_bit == 8)
  {
    fwrite (&bit_buffer, 1, 1, f);
    current_bit = 0;
    bit_buffer = 0;
  }
}

void Huffman::comprimeTexto(){
	calculaProbabilidade();
	geraArvore();
	code(arvoreDeProbabilidades, "");

	//printCod(arvoreDeProbabilidades);

	/*
	for(auto it=codigo.begin(); it!=codigo.end(); ++it){
		cout << "char: " << it->first << " codigo " << bitset<12>( it->second )
			 << dec << " tamanhoDoCodigo " << tamanhoDoCodigo[it->first] << endl;
	}
	*/
	arquivoCodificado.open(nomeArquivoCodificado.data(), ios::out | ios::binary );
	if ( arquivoCodificado.is_open() ){
		//noskipws
		int bitsInBuffer = 0;
		unsigned char bitBuffer;
		for(int i = 0; i < qntCaracteresEntrada; i++){
			//arquivoCodificado << codigo[textoEntrada[i]];
			//arquivoCodificado.write(, tamanhoDoCodigo[textoEntrada[i]]);
			string cod = codigo[textoEntrada[i]];
			for (char c : cod){
				int bit = c == '1' ? 1 : 0;


				if (bitsInBuffer > 7) {
					arquivoCodificado.write((char*)&bitBuffer, 1);
					bitsInBuffer = 0;
					bitBuffer = 0;
				}
				bitBuffer = (bitBuffer << 1) | (bit);
				bitsInBuffer++;
			}
		}

		if (bitsInBuffer > 0){ // enche com zeros
			//cout << "entra no if " << bitsInBuffer << endl;
  			do {
  				//cout << "uma vez no loop" << endl;
  				if (bitsInBuffer > 7) {
  					//cout << "bitbuffer "<< bitset<8>(bitBuffer) << endl;
    				arquivoCodificado.write((char*)&bitBuffer, 1);
    				bitsInBuffer = 0;
    				bitBuffer = 0; // just to be tidy
				}

  				bitBuffer = (bitBuffer << 1) | 0;
  				bitsInBuffer++;
  			} while (bitsInBuffer != 1);
  		}
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
