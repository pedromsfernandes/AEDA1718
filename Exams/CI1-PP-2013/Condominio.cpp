/*
 * Condominio.cpp
 */

#include "Condominio.h"

//Imovel

Imovel::Imovel(int areaH, string prop, int id): areaHabitacao(areaH), proprietario(prop), ID(id)
{}

int Imovel::getID() const
{ return ID; }

void Imovel::setID(int id)
{ ID=id; }

int Imovel::getAreaHabitacao() const
{ return areaHabitacao; }

string Imovel::getProprietario() const
{ return proprietario; }

//Apartamento

Apartamento::Apartamento(int areaH, int anda, string prop, int id): Imovel(areaH,prop,id), andar(anda)
{}

float Apartamento::mensalidade() const
{
	return 50+0.2*Imovel::getAreaHabitacao()+andar;
}


int Apartamento::areaTotal() const
{
	return Imovel::getAreaHabitacao();
}

//Vivenda

Vivenda::Vivenda(int areaH, int areaExt, bool pisc, string prop, int id):Imovel(areaH,prop,id), areaExterior(areaExt), piscina(pisc)
{}


float Vivenda::mensalidade() const
{
	return 50+0.2*Imovel::getAreaHabitacao()+0.1*areaExterior+10*piscina;
}

int Vivenda::areaTotal() const
{
	return Imovel::getAreaHabitacao() + areaExterior;
}

//Urbanizacao

Urbanizacao::Urbanizacao(string nm, int id): nome(nm), ID(id)
{}


void Urbanizacao::adicionaImovel(Imovel *im1)
{
	Imovel* temp = im1;

	temp->setID(imID);
	imID++;
	imoveis.push_back(temp);
}

vector<Imovel *> Urbanizacao::areaSuperiorA(int area1) const
{
	vector<Imovel *> areaSup;

	for(int i=0;i<imoveis.size();++i)
		if(imoveis.at(i)->areaTotal()>area1)
			areaSup.push_back(imoveis.at(i));

	return areaSup;
}

vector<Imovel *> Urbanizacao::getImoveis() const
{ return imoveis; }

string Urbanizacao::getNome() const
{ return nome; }

int Urbanizacao::getID() const
{ return ID; }

bool Urbanizacao::operator>(const Urbanizacao &e2)
{
	vector<string> props1;
	vector<string> props2;
	bool existe=false;

	int num1=imoveis.size(), num2=e2.getImoveis().size();

	double raz1, raz2;

	if(num1==0)
		return false;
	if(num2==0)
		return true;

	for(int i=0;i<num1;++i)
		{
			for(int j=0;j<props1.size();++j)
				if(imoveis.at(i)->getProprietario()==props1.at(j))
					existe=true;

			if(!existe)
				props1.push_back(imoveis.at(i)->getProprietario());

			existe=false;
		}

	existe=false;

	for(int i=0;i<num2;++i)
		{
			for(int j=0;j<props2.size();++j)
				if(e2.getImoveis().at(i)->getProprietario()==props2.at(j))
					existe=true;

			if(!existe)
				props2.push_back(e2.getImoveis().at(i)->getProprietario());

			existe=false;
		}

	raz1=num1/props1.size();
	raz2=num2/props2.size();

	return raz1<raz2;

}

Urbanizacao::Urbanizacao(string nm)
{
	nome=nm;
	ID=IDseq++;
	imID=1;
}

int Urbanizacao::IDseq =1;

void Urbanizacao::resetID()
{
	IDseq=1;
}

//ECondominio

void ECondominio::adicionaUrbanizacao(Urbanizacao urb1)
{ urbanizacoes.push_back(urb1); }

vector<Urbanizacao> ECondominio::getUrbanizacoes() const
{ return urbanizacoes; }

float ECondominio::mensalidadeDe(string nomeProp) const
{
	float sum=0;

	for(int i=0;i<urbanizacoes.size();++i)
		for(int j=0;j<urbanizacoes.at(i).getImoveis().size();++j)
			if(urbanizacoes.at(i).getImoveis().at(j)->getProprietario()==nomeProp)
				sum+=urbanizacoes.at(i).getImoveis().at(j)->mensalidade();

	return sum;
}

vector<Urbanizacao> ECondominio::removeUrbanizacaoDe(string nomeProp)
{
	vector<Urbanizacao> removidas;

	for(int i=0;i<urbanizacoes.size();++i)
			for(int j=0;j<urbanizacoes.at(i).getImoveis().size();++j)
				if(urbanizacoes.at(i).getImoveis().at(j)->getProprietario()==nomeProp)
				{
					removidas.push_back(urbanizacoes.at(i));
					urbanizacoes.erase(urbanizacoes.begin()+i);
					i--;
					break;
				}

	return removidas;
}

vector<Imovel*> ECondominio::operator() (string nomeUrb)
{
	for(int i=0;i<urbanizacoes.size();++i)
		if(urbanizacoes.at(i).getNome()==nomeUrb)
			return urbanizacoes.at(i).getImoveis();

	vector<Imovel*> v1;

	return v1;
}
