
#ifndef CLUBEVIDEO_H_
#define CLUBEVIDEO_H_

#include <string>
#include <stack>
#include <queue>
#include <list>
#include <ostream>
#include <sstream>
#include <algorithm>
using namespace std;

class Filme {
	string titulo;
	int emprestimos;
public:
	Filme(string umTitulo):titulo(umTitulo), emprestimos(0) {}
	string getTitulo() const { return titulo; }
	int getEmprestimos() const { return emprestimos; }
	void addEmprestimos() { emprestimos++; }
	bool operator==(const Filme& f1) const{ return (this->titulo == f1.titulo); }
	friend ostream& operator<<(ostream& os, const Filme& dvd);
};

class Cliente {
	string nome;
	stack<Filme> filmesEmprestados;
public:
	Cliente(string umNome):nome(umNome){}
	string getNome() const{ return nome; }
	void addFilme(Filme umFilme){ filmesEmprestados.push(umFilme); }
	stack<Filme> getFilmesEmprestados() const{ return filmesEmprestados; }
	Filme devolver(string umTitulo);
	bool operator==(const Cliente& c1) const{ return (this->nome == c1.nome); }
	friend ostream& operator<<(ostream& os, const Cliente& c1);
};

class PedidoCliente {
	string nome;
	string titulo;
public:
	PedidoCliente(string nomeC, string tituloF): nome(nomeC), titulo(tituloF) {}
	string getNomeCliente() const { return nome; }
	string getTituloFilme() const { return titulo; }
	bool operator==(const PedidoCliente& pc1) const {
		return ((this->nome == pc1.nome) && (this->titulo == pc1.titulo) );
	}
	friend ostream& operator<<(ostream& os, const PedidoCliente& pc);
};

class ClubeVideo {
	vector<Filme> filmes;
	vector<Cliente> clientes;
	queue<PedidoCliente> pedidos;
public:
	ClubeVideo(){}
	void addCliente(Cliente umCliente) { clientes.push_back(umCliente); }
	void addFilme(Filme umFilme) { filmes.push_back(umFilme); }
	void addPedidoCliente(PedidoCliente umPedido) { pedidos.push(umPedido); }
	int numFilmes() const { return filmes.size(); }
	int numClientes() const { return clientes.size(); }
	int numPedidos() const { return pedidos.size(); }

	bool existeCliente(string umNome) const;
	bool existeFilme(string umTitulo) const;
	string imprimirFilmes() const; //imprime todos; emprestados e n�o emprestados!
	list<string> titulosDisponiveis() const; //lista dos t�tulos, n�o repetidos
	bool tituloDisponivel(string umTitulo) const;
	string imprimirListaDeEspera() const;
	void alugar(string umNome, string umTitulo); //
	void devolver(string umNome, string umTitulo);
};

class FilmeInexistente{
private:
	string nome;
public:
	FilmeInexistente(string nome);
	string msg();
};



#endif /* CLUBEVIDEO_H_ */
