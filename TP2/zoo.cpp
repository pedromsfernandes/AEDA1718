#include "zoo.h"
#include <iterator>
#include <string>


//Animal

Animal::Animal(string nome, int idade)
{
	this->nome=nome;
	this->idade=idade;
	vet=NULL;

	if(idade<maisJovem || maisJovem<0)
		maisJovem=idade;
}

int Animal::maisJovem = -1;

string Animal::getNome() const {
	return nome;
}

void Animal::setVeterinario(Veterinario *vet)
{
	this-> vet = vet;
}

Veterinario* Animal::getVeterinario() const
{
	return vet;
}

string Animal::getInformacao() const
{
	string inf;

	inf = nome + ", " + to_string(idade);

	if(vet!=NULL)
		inf+=", " + vet->getInformacao();

	return inf;
}

int Animal::getIdade() const
{
	return idade;
}

int Animal::getMaisJovem()
{
	return maisJovem;
}


//Cao

Cao::Cao(string nome, int idade, string raca):Animal(nome,idade)
{
	this->raca=raca;
}

bool Cao::eJovem() const
{
	if(idade<5)
		return true;

	return false;
}

string Cao::getInformacao() const
{
	string inf;

	inf= Animal::getInformacao() + ", " + raca;

	return inf;
}


//Morcego

Morcego::Morcego(string nome, int idade, int vmax, int amax):Animal(nome, idade),Voador(vmax,amax)
{
}

bool Morcego::eJovem() const
{
	if(idade<4)
			return true;

	return false;
}

string Morcego::getInformacao() const
{
	string inf;

	inf= Animal::getInformacao() + ", " + Voador::getInformacao();

	return inf;
}


//Veterinario

Veterinario::Veterinario(string nome, int cod)
{
	this->nome=nome;
	this->codOrdem=cod;
}

string Veterinario::getNome() const {
	return nome;
}

string Veterinario::getInformacao() const
{
	string inf;

	inf = nome + ", " + to_string(codOrdem);
	cout << inf << endl;

	return inf;
}



//Voador

Voador::Voador(int vmax, int amax)
{
	velocidade_max=vmax;
	altura_max=amax;
}

string Voador::getInformacao() const
{
	string inf;

	inf = to_string(velocidade_max) + ", " + to_string(altura_max);

	return inf;
}


//Zoo

void Zoo::alocaVeterinarios(istream &isV)
{
	string name, cod;
	unsigned int vetCounter=0;

	while(!isV.eof())
	{
		getline(isV,name);
		getline(isV,cod);


		if(name=="")
			break;

		Veterinario *v1 = new Veterinario(name, stoi(cod));
		veterinarios.push_back(v1);
	}

	for(vector<Animal*>::iterator it=animais.begin();it<animais.end();it++)
	{
		(*it)->setVeterinario(veterinarios.at(vetCounter));

		if(vetCounter==veterinarios.size()-1)
			vetCounter=0;
		else
			vetCounter++;
	}
}

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

bool Zoo::removeVeterinario(string nomeV)
{
	bool exists=false;
	vector<Veterinario*>::iterator it;

	for(it=veterinarios.begin();it!=veterinarios.end();++it)
		{
			if((*it)->getNome()==nomeV){
				exists=true;
				break;
			}
		}

	if(exists==false)
		return exists;

	for(vector<Animal*>::iterator it2=animais.begin();it2!=animais.end();++it2)
		if((*it2)->getVeterinario()->getNome()==nomeV)
			(*it2)->setVeterinario((*(++it)));


	veterinarios.erase(--it);

	return exists;

}

void Zoo::adicionaAnimal(Animal *a1)
{
	animais.push_back(a1);
}

string Zoo::getInformacao()const
{
	string inf;

	for(vector<Animal *>::const_iterator it=animais.begin();it<animais.end();++it){
		inf+=(*it)->getInformacao() + "\n";
	}

	return inf;
}

bool Zoo::animalJovem(string nomeA)
{
	bool exists=false, young=false;

	for(vector<Animal*>::iterator it=animais.begin();it<animais.end();it++){
		if((*it)->getNome()==nomeA){
			exists=true;

			if((*it)->eJovem())
				young=true;

			break;
		}
	}

	if(exists && young)
		return true;

	return false;

}

vector<Animal *> Zoo::getAnimais() const
{
	return animais;
}

bool Zoo::operator < (Zoo& zoo2) const
{
	int sum1=0, sum2=0;

	for(vector<Animal*>::const_iterator it=animais.begin();it!=animais.end();++it)
		sum1+=(*it)->getIdade();

	for(vector<Animal*>::const_iterator it=zoo2.getAnimais().begin();it!=zoo2.getAnimais().end();++it)
		sum2+=(*it)->getIdade();

	if(sum1<sum2)
		return true;

	return false;
}
