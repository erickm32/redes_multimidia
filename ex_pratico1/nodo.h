using namespace std;

struct Nodo {
	Nodo *filhoEsquerda, *filhoDireita;
	Nodo *raiz;
	float probabilidade;
	char simbolo;
	string codigo;

	Nodo(Nodo* esq, Nodo* dir, Nodo* raiz, float probabilidade, char simbolo){
		this->filhoEsquerda = esq; 
		this->filhoDireita = dir;
		this->raiz = raiz;
		this->probabilidade = probabilidade;
		this->simbolo = simbolo;
	}

	Nodo(){
		this->filhoEsquerda = NULL;
		this->filhoDireita = NULL;
		this->raiz = NULL;
		this->probabilidade = 0;
		this->simbolo = '\0';
		this->codigo = "";
	}

	Nodo(const Nodo& n){
		//cout << "copia e " << n.probabilidade << " & " << &n << "\n";
		this->filhoEsquerda = n.filhoEsquerda;
		this->filhoDireita = n.filhoDireita;
		this->raiz = n.raiz;
		this->probabilidade = n.probabilidade;
		this->simbolo = n.simbolo;
		this->codigo = n.codigo;
	}

	bool operator==(const Nodo &n) const {
        return this->probabilidade == n.probabilidade;
    }

    bool operator!=(const Nodo &n) const {
        return (this->probabilidade != n.probabilidade);
    }

    bool operator<(const Nodo &n) const {
        return (this->probabilidade > n.probabilidade);
    }

    bool operator<=(const Nodo &n) const {
        return (this->probabilidade >= n.probabilidade);
    }

    bool operator>(const Nodo &n) const {
        return (this->probabilidade < n.probabilidade);
    }

    bool operator>=(const Nodo &n) const {
        return (this->probabilidade <= n.probabilidade);
    }
};