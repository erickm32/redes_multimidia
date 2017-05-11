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
		this->codigo = "";
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