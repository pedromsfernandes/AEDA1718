
#ifndef COOPERATIVA_H_
#define COOPERATIVA_H_

#include <string>
#include <list>
#include <sstream>
#include <tr1/unordered_set>
#include "BST.h"

using namespace std;


class Vinho {
	string nome;
	int ano;
public:
	Vinho(string umNome, int umAno): nome(umNome), ano(umAno) {}
	Vinho(string umNome) : nome(umNome){}
	Vinho(){}
	string getNome() const { return nome; }
	int getAno() const { return ano; }
	friend ostream& operator<<(ostream& os, const Vinho& v1) {
		os << v1.nome << " " << v1.ano;
		return os;
	}

	bool operator<(const Vinho& v1) const;
	bool operator==(const Vinho& v1) const;
};

class Vinicola {
	string nome;
	int vinhos;
public:
	Vinicola(string umNome):nome(umNome), vinhos(1) {}
	string getNome() const { return nome; }
	int getVinhos() const { return vinhos; }
	void setNome(string umNome) { nome = umNome; }
	void setVinhos(int vs) { vinhos = vs; }
	void addVinho() { vinhos++; }

	bool operator<(const Vinicola& v1) const;
	bool operator==(const Vinicola& v1) const;
};

class Enologo {
	string nome;
	list<Vinicola> vinicolas;
public:
	Enologo(string umNome): nome(umNome) { }
	string getNome() const { return nome; };
	list<Vinicola> getVinicolas() const { return vinicolas; };
	void addVinicolaInexistente(const Vinicola &v1) { vinicolas.push_back(v1); }
	bool operator<(const Enologo& e1) const;
	bool operator==(const Enologo& e1) const;
	list<Vinicola>::iterator existsVinicola(string umaVinicola);
	int getNumVinhos() const;
	list<Vinicola>::iterator getEnd();
};

struct hVinicola {

	int operator()(const Vinicola& v1) const{
		int v = 0;
		for ( unsigned int i=0; i< v1.getNome().size(); i++ )
			v = 37*v + v1.getNome()[i];
		return v;
	}

	bool operator()(const Vinicola& v1, const Vinicola& v2) const {
		return v1.getNome()==v2.getNome();
	}

};

typedef tr1::unordered_set<Vinicola, hVinicola, hVinicola> hashVinicola;

class Cooperativa {
	BST<Vinho> vinhos;
	hashVinicola vinicolas;
	priority_queue<Enologo> enologos;
public:
	//TODO: Implementar corretamente o construtor e inicializacao da BST!
	Cooperativa();
	BST<Vinho> getVinhos() const { return vinhos; }
	void addVinho(Vinho &v1) { vinhos.insert(v1); }
	void addVinhos(const vector<Vinho>& vv);
	list<string> vinhosDisponiveis(int ano1, int ano2);
	int delVinhoNome(string umVinho);
	void add_Vinicola(const Vinicola &v1) { vinicolas.insert(v1);	}
	hashVinicola getVinicolas() const { return vinicolas; }
	void addVinicola(string umaVinicola);
	Vinicola maisOpcoes();
	void addEnologo(const Enologo & e1)  {enologos.push(e1); }
	priority_queue<Enologo> getEnologos() const { return enologos; }
	void addEnologoVinicola(string umEnologo, string umaVinicola);
	list<Vinicola> vinicolasMelhoresNEnologos(int n);
};

#endif /* COOPERATIVA_H_ */
