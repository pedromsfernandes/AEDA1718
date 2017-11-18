/*
 * SuperMercado.h
 *
 * Created on: 2 Dec 2014
 *
 */

#ifndef SRC_SUPERMERCADO_H_
#define SRC_SUPERMERCADO_H_

#include <stack>
#include <string>
#include <sstream>
#include <list>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

class Item {
public:
	int preco;
	int volume;
	int peso;
	string produto;
	string tipo;
	Item(int umPreco, int umVolume, int umPeso, string umProduto, string umTipo):
		preco(umPreco), volume(umVolume), peso(umPeso), produto(umProduto), tipo(umTipo)
	{ /*...*/ }
	bool operator<(const Item &i1);
};

class Cesto {
	int max_volume, volume;
	int max_peso, peso;
	stack<Item> itens;
public:
	Cesto()	{
		max_volume = 10; max_peso = 10;
		volume = 0; peso = 0;
	}
	Cesto(vector<Item> unsItens) {
		max_volume = 10; max_peso = 10;
		volume = 0; peso = 0;
		for(unsigned int i = 0; i < unsItens.size(); i++) itens.push(unsItens[i]);
	}
	stack<Item> getItens() const { return itens; }
	Item& topItem(){ return itens.top(); }
	void popItem(){ if(!itens.empty()) itens.pop(); }
	void pushItem(const Item& umItem){ itens.push(umItem); }
	bool empty() const{ return itens.empty(); }
	int numItens() const;
	int valor() const;
	int trocarItem(Item& novoItem);
	void organizarCesto();
	map<string,unsigned int> contarItensPorTipo();
	int novoItem(const Item& umItem);
	int getVolume() const;
	int getPeso() const;
};

class Cliente {
	list<Cesto> cestos;
	string nome;
	int idade;
public:
	Cliente(){ nome = ""; idade = 0; }
	Cliente(string umNome, int umaIdade): nome(umNome), idade(umaIdade) { /*...*/ }
	string getNome() const { return nome; }
	int getIdade() const { return idade; }
	list<Cesto> getCestos() const { return cestos; }

	int addCesto(Cesto& umCesto)
	{
		cestos.push_back(umCesto);
		return cestos.size();
	}
	int numCestos() const { return cestos.size(); }
	int numeroItens() const;
	int valorItens() const;
	int trocarItem(Item& novoItem);
	void organizarCestos();
	vector<string> contarItensPorTipo();
	int novoItem(const Item& umItem);
};

class Supermercado {
	queue<Cliente> filaNormal;
	queue<Cliente> filaPrioritaria;
public:
	Supermercado() { /*...*/ }
	int tamanhoFilaNormal() const { return filaNormal.size(); }
	int tamanhoFilaPrioritaria() const { return filaPrioritaria.size(); }
	void setFilaNormal(queue<Cliente>& fn) { filaNormal = fn; }
	void setFilaPrioritaria(queue<Cliente>& fp) { filaPrioritaria = fp; }
	queue<Cliente> getFilaNormal() const { return filaNormal; }
	queue<Cliente> getFilaPrioritaria() const { return filaPrioritaria; }

	int novoCliente(Cliente& umCliente);
	Cliente sairDaFila(string umNomeDeCliente);
	class ClienteInexistente{
	private:
		string nome;
	public:
		ClienteInexistente(string nome){this->nome=nome;};
		string getNome() const {return nome;};
	};

};



#endif /* SRC_SUPERMERCADO_H_ */
