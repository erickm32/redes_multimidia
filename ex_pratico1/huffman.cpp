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

void Huffman::comprimeTexto(){
	calculaProbabilidade();
	geraArvore();
	code(arvoreDeProbabilidades, "");
	arquivoCodificado.open(nomeArquivoCodificado.data(), ios::out | ios::binary );
	if ( arquivoCodificado.is_open() ){
		// altamente inspirado em
		// http://stackoverflow.com/questions/28573597/bitstream-of-variable-length-huffman-codes-how-to-write-to-file?rq=1
		int bitsInBuffer = 0;
		unsigned char bitBuffer;
		for(int i = 0; i < qntCaracteresEntrada; i++){
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

		if (bitsInBuffer > 0){ // enche com zeros o restante pra fechar um byte
  			do {
  				if (bitsInBuffer > 7) {
    				arquivoCodificado.write((char*)&bitBuffer, 1);
    				bitsInBuffer = 0;
    				bitBuffer = 0;
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

map<char, float> Huffman::probsParser(){
	if(!arquivoProbabilidades.is_open()){
		arquivoProbabilidades.open(nomeArquivoProbabilidades, ios::in);
	}
	map<char, float> probsLidas;
	if(arquivoProbabilidades.is_open()){
		string linha;
		while(!arquivoProbabilidades.eof()){
			arquivoProbabilidades  >> linha;
			if(arquivoProbabilidades.eof()) break;

			if(linha == "bytes"){
				arquivoProbabilidades >> linha;
				numeroBytesCodificados = stoi(linha);
			}
			if(linha[0] >= 'A' && linha[0] <= 'Z'){
				char c = linha[0];
				arquivoProbabilidades  >> linha;
				probsLidas[c] = stof(linha);
			}

		}
	}
	else{
		cerr << "Erro ao ler o arquivo de probabilidades" << endl;
	}
	arquivoProbabilidades.close();
	return probsLidas;
};

void Huffman::descomprimeTexto(){
	arquivoCodificado.open(nomeArquivoCodificado.data(), ios::in | ios::binary );
	//arquivoProbabilidades.open(nomeArquivoProbabilidades.data(), ios::in );
	arquivoDecodificado.open(nomeArquivoDecodificado.data(), ios::out);

	hash_caracteres.clear();
	hash_caracteres = probsParser();
	if(hash_caracteres.empty()){
		cerr << "Não conseguiu remontar as probabilidades dos caracteres." << endl;
		exit(1);
	}

	for (auto it=hash_caracteres.begin(); it!=hash_caracteres.end(); ++it){
			Nodo *nodo = new Nodo(NULL, NULL, NULL, it->second, it->first);
			pq.push(*nodo);
    		delete nodo;
		}
	arvoreDeProbabilidades = NULL;
	geraArvore();
	code(arvoreDeProbabilidades, "");

	if ( !arquivoCodificado.is_open() ){
		cerr << "Não foi possível ler o arquivo codificado" << endl;
	}
	if ( !arquivoDecodificado.is_open() ){
		cerr << "Não foi possível ler o arquivo codificado" << endl;
	}

	unsigned char byte = 0;
	int bitsInBuffer, bit = 0;
	string codeReaded;
	char simbolo;
	int numBytesLidos = 0;
	while(!arquivoCodificado.eof() && numBytesLidos < numeroBytesCodificados ){
		arquivoCodificado.read((char*)&byte, 1);
		if(arquivoCodificado.eof()) break;
		bitsInBuffer = 8;

		while(bitsInBuffer > 0){
			bit = byte & 0x80; // 10000000
			byte = byte << 1;
			--bitsInBuffer;
			codeReaded.push_back(bit == 0x80 ? '1' : '0');
			simbolo = findSymbol(arvoreDeProbabilidades, codeReaded);
			if(simbolo != '\0' && numBytesLidos < numeroBytesCodificados){
				arquivoDecodificado << simbolo;
				numBytesLidos+=1;
				codeReaded = "";
			}
		}

	}


	arquivoDecodificado.close();
	arquivoCodificado.close();

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


string Huffman::getTextoEntrada(){
	return textoEntrada;
};
