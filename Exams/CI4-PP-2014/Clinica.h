
#ifndef CLINICA_H_
#define CLINICA_H_

#include <string>
#include <list>
#include <sstream>
#include <tr1/unordered_set>
#include "BST.h"



class Animal {
	string nome;
	string especie;
	int numConsultas;
public:
	Animal(string umNome, string umaEspecie, int numeroConsultas=0);
	string getNome() const;
	string getEspecie() const;
	int getNumConsultas() const;
	void incNumConsultas();
};

class Veterinario {
	string nome;
	list<string> meusAnimais;
public:
	Veterinario(string umNome);
	string getNome() const;
	list<string> getAnimais() const;
	void addAnimal(string umNomeAnimal);

	//TODO: A implementar (vide ficheiro CPP)
	bool operator<(const Veterinario& v1) const;
};

class Consulta {
	int hora, dia, mes;
	string nomeAnimal;
public:
	Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal="");
	string getNomeAnimal() const;
	int getHora() const;
	int getDia() const;
	int getMes() const;
	void setAnimal(string nome);

	//TODO: A implementar (vide ficheiro CPP)
	bool operator < (const Consulta &c2) const;
};

class ConsultasVet {
public:
	string nomeVeterinario;
	BST<Consulta> minhasConsultas;
	ConsultasVet(string umNomeVet);
	void addConsulta(const Consulta &c1);
	list<Consulta> consultasDisponiveis(int dia1, int dia2, int mesC) const;

};



struct hAnimal {
	int operator()(const Animal& a1) const{
		int v = 0;
		for ( unsigned int i=0; i< a1.getNome().size(); i++ )
			v = 37*v + a1.getNome()[i];
		return v;

	}
	bool operator()(const Animal& a1, const Animal& a2) const {

		return a1.getNome()==a2.getNome();
	}
};

typedef tr1::unordered_set<Animal, hAnimal, hAnimal> hashAnimal;

class Clinica {
	list<ConsultasVet> consultasDisponiveis;
	hashAnimal animais;
	priority_queue<Veterinario> veterinarios;
public:
	Clinica();
	list<ConsultasVet> getConsultasDisponiveis() const;
	hashAnimal getAnimais() const;
	priority_queue<Veterinario> getVeterinarios() const;
	void addConsultasDisponiveisVet(const ConsultasVet &v1);
	void addAnimal(const Animal &a1);
	void addVeterinario(const Veterinario &v1);

	//TODO: a realizar de acordo com o solicitado nas respectivas al�neas!

	void addConsultas(const vector<Consulta> consultas1, string nomeVet);
	list<Consulta> veConsultasDisponiveis(int dia1, int dia2, int mesC, string nomeVet) const;
	bool marcaConsulta(int &horaC, int &diaC, int &mesC, string nomeAnimal, string nomeVet);
	Animal fimConsulta(string umNomeAnimal, string umNomeEspecie);
	int numAnimaisEspecie(string umNomeEspecie) const;
	Veterinario alocaVeterinario(string umNomeAnimal);
	list<string> veterinariosMaisN(int n) const;

};

#endif /* CLINICA_H_ */
