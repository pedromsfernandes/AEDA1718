#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include <algorithm>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes.at(posicaoCliente(nome)).frequencia++;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

ClienteNaoExistente::ClienteNaoExistente(string nome)
{
	this->nome=nome;
}

string ClienteNaoExistente::getNome() const
{
	return nome;
}

PosicaoNaoExistente::PosicaoNaoExistente(unsigned int valor)
{
	this->valor=valor;
}

unsigned int PosicaoNaoExistente::getValor() const
{
	return valor;
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
	if( p > clientes.size() || p < 0)
		throw PosicaoNaoExistente(p);

	return clientes.at(p);
}


int ParqueEstacionamento::getFrequencia(const string &nome) const
{
	if(posicaoCliente(nome)==-1)
		throw ClienteNaoExistente(nome);

	else return(clientes.at(posicaoCliente(nome)).frequencia);
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {

	vector<string> nomes;

	for(int i=0;i<clientes.size();++i)
		nomes.push_back(clientes.at(i).nome);

	return(sequentialSearch(nomes,nome));
}


void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
	insertionSort(clientes);
}

bool InfoCartao::operator < (const InfoCartao &ic1) const
{
	if(frequencia==ic1.frequencia)
		return nome<ic1.nome;

	else
		return frequencia > ic1.frequencia;
}


vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
	vector<InfoCartao> c1;
	vector<string> nomes;

	for(int i=0;i<clientes.size();++i)
		if(clientes.at(i).frequencia>=n1 && clientes.at(i).frequencia<=n2)
			c1.push_back(clientes.at(i));

	insertionSort(c1);

	for(int i=0;i<c1.size();++i)
		nomes.push_back(c1.at(i).nome);

	return nomes;
}

bool menorCliente(const InfoCartao &c1, const InfoCartao &c2)
{
	return c1.nome<c2.nome;
}

void ParqueEstacionamento::ordenaClientesPorNome()
{
	sort(clientes.begin(),clientes.end(),menorCliente);
}


string InfoCartao::getInformacao() const
{
	string inf;

	inf += "Nome do cliente: " + nome + ", ";
	inf += "Presenca: ";

	if(presente)
		inf+=" presente";
	else
		inf+="nao presente";

	inf += ", Frequencia: " + to_string(frequencia) + "\n";

	return inf;
}

ostream & operator << (ostream &os, const ParqueEstacionamento &pe)
{
	for(int i=0;i<pe.getClientes().size();++i)
		cout << pe.getClientes().at(i).getInformacao();

	return os;
}
