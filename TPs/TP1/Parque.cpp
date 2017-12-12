#include "Parque.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : numMaximoClientes(nMaxCli), lotacao(lot)
{
	vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	for(int i=0;i<clientes.size();++i)
	{
		if(clientes[i].nome==nome)
			return i;
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	if(clientes.size()<numMaximoClientes)
	{
		InfoCartao inf;
		inf.nome=nome;
		inf.presente=false;

		clientes.push_back(inf);
		return true;
	}
	else
		return false;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	bool registed=false, present=false;
	int index;

	for(int i=0;i<clientes.size();++i)
		if(clientes.at(i).nome==nome && clientes.at(i).presente==true)
			{
			present=true;
			registed=true;
			}
		else if(clientes.at(i).nome==nome)
		{
			index=i;
			registed=true;
			present=false;
		}

	if(registed == false || present == true || vagas==0)
		return false;
	else
	{
		--vagas;
		clientes.at(index).presente=true;
		return true;
	}
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for(int i=0;i<clientes.size();++i)
	{
		if(clientes.at(i).nome==nome && clientes.at(i).presente==false)
		{
			clientes.erase(clientes.begin()+i);
			return true;
		}
	}

	return false;
}

bool ParqueEstacionamento::sair(const string & nome)
{

	bool registed=false, present=false;
	int index;

	for(int i=0;i<clientes.size();++i)
	{
		if(clientes.at(i).nome==nome && clientes.at(i).presente==true)
		{
			present=true;
			registed=true;
			index=i;
		}
		else if(clientes.at(i).nome==nome)
		{
			registed = true;
			present= false;
		}
	}

	if(!registed || !present)
		return false;
	else
	{
		++vagas;
		clientes.at(index).presente=false;
		return true;
	}

}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
	return clientes.size();
}

const ParqueEstacionamento & ParqueEstacionamento::operator+=(const ParqueEstacionamento & p2)
{
	for(int i=0;i<p2.clientes.size();++i)
	{
		if(clientes.size()>=numMaximoClientes)
			return *this;

		adicionaCliente(p2.clientes.at(i).nome);
	}

	return *this;
}
