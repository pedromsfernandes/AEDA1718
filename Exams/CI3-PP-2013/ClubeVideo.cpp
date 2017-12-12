#include "ClubeVideo.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Filme& umFilme) {
	os << umFilme.getTitulo() << " " << umFilme.getEmprestimos();
	return os;
}

ostream& operator<<(ostream& os, const PedidoCliente& pc) {
	os << "Cliente " << pc.getNomeCliente() << " em espera para " << pc.getTituloFilme() << endl;
	return os;
}

ostream& operator<<(ostream& os, const Cliente& c1) {
	os << c1.getNome() << " tem " << c1.getFilmesEmprestados().size() << " filmes!\n";
	return os;
}


//
// Incluir abaixo a implementa��o das suas fun��es
//


bool ClubeVideo::existeCliente(string umNome) const
{
	for(int i=0;i<clientes.size();i++){
		if(clientes.at(i).getNome()==umNome)
			return true;
	}

	return false;
}

bool ClubeVideo::existeFilme(string umTitulo) const
{
	stack<Filme> emp;

	for(int i=0;i<clientes.size();i++){
		emp=clientes.at(i).getFilmesEmprestados();
		while(!emp.empty()){
			if(emp.top().getTitulo()==umTitulo)
				return true;
			emp.pop();
		}

	}

	for(int i=0;i<filmes.size();i++)
		if(filmes.at(i).getTitulo()==umTitulo)
			return true;

	return false;
}

string ClubeVideo::imprimirFilmes() const{

	ostringstream s;
	stack<Filme> st;

	for(int i=0;i<filmes.size();i++)
		s << filmes.at(i) << "\n";

	for(int i=0;i<clientes.size();i++){
		st=clientes.at(i).getFilmesEmprestados();
		while(!st.empty()){
			s << st.top() << "\n";
			st.pop();
		}
	}

	return s.str();
}


bool existe(string n, list<string> l)
{
	for(auto it=l.begin();it!=l.end();it++)
		if((*it)==n)
			return true;

	return false;
}

bool existe3(string c, vector<Cliente> v){

	for(auto it=v.begin();it!=v.end();it++)
		if(it->getNome()==c)
			return true;

	return false;
}

bool existe2(string n, vector<Cliente> v1 ,vector<Filme> v2)
{
	stack<Filme> st;

	for(auto it=v2.begin();it!=v2.end();it++)
		if(it->getTitulo()==n)
			return true;

	for(auto it=v1.begin();it!=v1.end();it++){
		st=it->getFilmesEmprestados();
		while(!st.empty()){
			if(st.top().getTitulo()==n)
				return true;
			st.pop();
		}
	}

	return false;


}

list<string> ClubeVideo::titulosDisponiveis() const
{
	list<string> ret;

	for(int i=0;i<filmes.size();i++)
		if(!existe(filmes.at(i).getTitulo(),ret))
			ret.push_back(filmes.at(i).getTitulo());

	ret.sort();
	return ret;
}

bool ClubeVideo::tituloDisponivel(string umTitulo) const
{
	for(auto it=filmes.begin();it!=filmes.end();it++)
		if((*it)==umTitulo)
			return true;

	return false;
}

string ClubeVideo::imprimirListaDeEspera() const
{
	string s;
	vector<string> v;
	queue<PedidoCliente> q = pedidos;

	while(!q.empty()){
		string s1;
		s1+= q.front().getTituloFilme() + "\n";
		v.push_back(s1);
		q.pop();
	}

	sort(v.begin(),v.end());

	for(int i=0;i<v.size();i++)
		s+=v.at(i);

	return s;
}

FilmeInexistente::FilmeInexistente(string nome){
	this->nome=nome;
}

string FilmeInexistente::msg()
{
	return "Titulo Inexistente: " + nome;
}

void ClubeVideo::alugar(string umNome, string umTitulo){

	int clienteIndex;

	if(!existe2(umTitulo,clientes,filmes))
		throw FilmeInexistente(umTitulo);

	if(!existe3(umNome,clientes)){
		clientes.push_back(Cliente(umNome));
		clienteIndex = clientes.size()-1;
	}
	else{
		for(int i=0;i<clientes.size();i++)
			if(clientes.at(i).getNome()==umNome){
				clienteIndex=i;
				break;
			}
	}


	for(int i=0;i<filmes.size();i++){
		if(filmes.at(i).getTitulo()==umTitulo)
		{
			clientes.at(clienteIndex).addFilme(filmes.at(i));
			filmes.at(i).addEmprestimos();
			filmes.erase(filmes.begin()+i);
			return;
		}
	}

	pedidos.push(PedidoCliente(umNome,umTitulo));

}

Filme Cliente::devolver(string umTitulo)
{
	stack<Filme> st=filmesEmprestados;
	Filme f1(umTitulo);

	while(!filmesEmprestados.empty()){
		if(filmesEmprestados.top().getTitulo()!=umTitulo)
			st.push(filmesEmprestados.top());
		else
			f1=filmesEmprestados.top();

		filmesEmprestados.pop();
	}

	filmesEmprestados=st;

	return f1;
}

void ClubeVideo::devolver(string umNome, string umTitulo)
{
	Filme f(umTitulo);
	bool pedido=false;
	queue<PedidoCliente> q;

	for(int i=0;i<clientes.size();i++){
		if(clientes.at(i).getNome()==umNome)
		{
			f = clientes.at(i).devolver(umTitulo);
			break;
		}
	}

	while(!pedidos.empty())
	{
		if(pedidos.front().getTituloFilme() == umTitulo && !pedido){
			filmes.push_back(f);
			alugar(pedidos.front().getNomeCliente(),umTitulo);
			pedido=true;
		}
		else{
			q.push(pedidos.front());
		}

		pedidos.pop();
	}


	pedidos = q;

	if(pedido==false)
		filmes.push_back(f);

}


