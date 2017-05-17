#include "huffman.h"

using namespace std;

void Huffman::descomprimeTexto(string nomeArquivoProbabilidades,
							   string nomeArquivoCodificado, 
							   string nomeArquivoDecodificado){

	this->nomeArquivoProbabilidades = nomeArquivoProbabilidades;
	this->nomeArquivoCodificado = nomeArquivoCodificado;

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
