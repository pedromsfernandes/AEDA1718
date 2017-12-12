#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
	numPresentes = rand()%5 + 1;

}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	tempo_atual = 0;
	prox_saida = 0;
	clientes_atendidos = 0;
	prox_chegada = rand()%20 + 1;
}      


void Balcao:: proximoEvento()
{

	if(prox_chegada < prox_saida || clientes.empty()){
		tempo_atual+=prox_chegada;
		chegada();
	}
	else{
		tempo_atual+=prox_saida;
		saida();
	}

}


void Balcao::chegada()
{
	Cliente c1 = Cliente();

	clientes.push(c1);
	prox_chegada = rand()%20 + 1;

	if(clientes.size()==1)
		prox_saida = tempo_atual + c1.getNumPresentes()*tempo_embrulho;

	cout << "Instante atual: " << tempo_atual << endl;
	cout << "Num presentes do cliente: " << c1.getNumPresentes() << endl << endl;

}   


void Balcao::saida()
{
	Cliente c1 = getProxCliente();
	clientes_atendidos++;

	clientes.pop();
	prox_saida = tempo_atual + c1.getNumPresentes()*tempo_embrulho;

	cout << "Instante atual: " << tempo_atual << endl;
	cout << "Num presentes do cliente: " << c1.getNumPresentes() << endl << endl;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }

queue<Cliente> Balcao::getClientes() const
{
	return clientes;
}

ostream & operator << (ostream & out, const Balcao & b1)
{
	cout << "Numero clientes atendidos: " << b1.getClientesAtendidos() << endl;
	cout << "Numero clientes em espera: " << b1.getClientes().size() << endl << endl;

     return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {

	if(clientes.empty())
		throw FilaVazia();

	return clientes.front();

}

      
