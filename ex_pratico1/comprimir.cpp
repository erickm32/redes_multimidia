#include "huffman.h"

using namespace std;

void Huffman::comprimeTexto(string nomeArquivoEntrada, 
							string nomeArquivoProbabilidades,
							string nomeArquivoCodificado){

	ifstream arquivoEntrada(nomeArquivoEntrada);
	getline(arquivoEntrada, this->textoEntrada);
	
	this->qntCaracteresEntrada = this->textoEntrada.size();
	this->nomeArquivoProbabilidades = nomeArquivoProbabilidades;
	this->nomeArquivoCodificado = nomeArquivoCodificado;

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