
#include "Clinica.h"

//Animal

Animal::Animal(string umNome, string umaEspecie, int numeroConsultas):
nome(umNome), especie(umaEspecie), numConsultas(numeroConsultas)
{}

string Animal::getNome() const
{ return nome; }

string Animal::getEspecie() const
{ return especie; }

int Animal::getNumConsultas() const
{ return numConsultas; }

void Animal::incNumConsultas()
{ numConsultas++; }


// Veterinario

Veterinario::Veterinario(string umNome):nome(umNome)
{}

string Veterinario::getNome() const
{ return nome; }

list<string> Veterinario::getAnimais() const
{ return meusAnimais; }

void Veterinario::addAnimal(string umNomeAnimal)
{ meusAnimais.push_back(umNomeAnimal); }


// Consulta

Consulta::Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal):
							hora(umaHora), dia(umDia), mes(umMes), nomeAnimal(umNomeAnimal)
{}

string Consulta::getNomeAnimal() const
{ return nomeAnimal; }

int Consulta::getHora() const { return hora; }
int Consulta::getDia() const { return dia; }
int Consulta::getMes() const { return mes; }


void ConsultasVet::addConsulta(const Consulta &c1)
{ minhasConsultas.insert(c1); }


//Clinica

Clinica::Clinica()
{}

list<ConsultasVet> Clinica::getConsultasDisponiveis() const
{ return consultasDisponiveis; }

hashAnimal Clinica::getAnimais() const
{ return animais; }

priority_queue<Veterinario> Clinica::getVeterinarios() const
{ return veterinarios; }

void Clinica::addConsultasDisponiveisVet(const ConsultasVet &v1)
{ consultasDisponiveis.push_front(v1); }

void Clinica::addAnimal(const Animal &a1)
{ animais.insert(a1); }

void Clinica::addVeterinario(const Veterinario &v1)
{ veterinarios.push(v1); }

void Clinica::addConsultas(const vector<Consulta> consultas1, string nomeVet){

	for(list<ConsultasVet>::iterator it = consultasDisponiveis.begin();it!=consultasDisponiveis.end();it++){
		if(it->nomeVeterinario==nomeVet){
			for(int i=0;i<consultas1.size();i++){
				it->minhasConsultas.insert(consultas1.at(i));
				return;
			}
		}
	}

	ConsultasVet c(nomeVet);
	for(int i=0;i<consultas1.size();i++){
		c.minhasConsultas.insert(consultas1.at(i));
	}
	consultasDisponiveis.push_front(c);
}



list<Consulta> ConsultasVet::consultasDisponiveis(int dia1, int dia2, int mesC) const{

	BST<Consulta> temp = minhasConsultas;
	list<Consulta> ret;
	while(!temp.isEmpty()){
		Consulta c = temp.findMin();

		if(c.getMes()==mesC && c.getDia()>=dia1 && c.getDia()<=dia2)
			ret.push_back(c);

		temp.remove(c);
	}

	return ret;

}

list<Consulta> Clinica::veConsultasDisponiveis(int dia1, int dia2, int mesC, string nomeVet) const{

	list<Consulta> empty;

	for(list<ConsultasVet>::const_iterator it=consultasDisponiveis.begin();it!=consultasDisponiveis.end();it++){
		if(it->nomeVeterinario==nomeVet){
			return it->consultasDisponiveis(dia1,dia2,mesC);
		}
	}

	return empty;
}

void Consulta::setAnimal(string nome){
	nomeAnimal=nome;
}

bool Clinica::marcaConsulta(int &horaC, int &diaC, int &mesC, string nomeAnimal, string nomeVet){

	for(list<ConsultasVet>::iterator it=consultasDisponiveis.begin(); it!=consultasDisponiveis.end();it++){
		if(it->nomeVeterinario==nomeVet){

			BST<Consulta> temp = it->minhasConsultas;

			while(!temp.isEmpty()){

				Consulta c = temp.findMin();
				Consulta t(horaC,diaC,mesC);

				if(c.getHora()==horaC && c.getDia() == diaC && c.getMes()==mesC){
					temp.remove(c);
					it->minhasConsultas = temp;
					return true;
				}
				else if(t<c){
					horaC=c.getHora();
					diaC=c.getDia();
					mesC=c.getMes();
					temp.remove(c);
					it->minhasConsultas = temp;
					return true;
				}
				else
					temp.remove(c);
			}

		}
	}

	return false;
}


Animal Clinica::fimConsulta(string umNomeAnimal, string umNomeEspecie)
{
	for(hashAnimal::iterator it =animais.begin(); it!=animais.end();it++){
		if(it->getNome()==umNomeAnimal){

			Animal temp = (*it);
			animais.erase(temp);
			temp.incNumConsultas();

			animais.insert(temp);
			return temp;
		}
	}

	Animal animal(umNomeAnimal, umNomeEspecie,1);
	animais.insert(animal);

	return animal;
}

int Clinica::numAnimaisEspecie(string umNomeEspecie) const{

	int counter =0;

	for(hashAnimal::const_iterator it =animais.begin(); it!=animais.end();it++){
		if(it->getEspecie()==umNomeEspecie){
			counter++;
		}
	}

	return counter;

}

Veterinario Clinica::alocaVeterinario(string umNomeAnimal){

	Veterinario vet = veterinarios.top();
	veterinarios.pop();
	vet.addAnimal(umNomeAnimal);
	veterinarios.push(vet);

	return vet;
}

list<string> Clinica::veterinariosMaisN(int n) const{

	list<string> names;
	priority_queue<Veterinario> temp = veterinarios;

	while(!temp.empty()){

		if(temp.top().getAnimais().size()>n)
			names.push_back(temp.top().getNome());

		temp.pop();
	}

	names.reverse();

	return names;
}
/////////////////////////////////////////////////////////////////////////


//TODO: Implementar corretamente o construtor e inicializacao da BST!
ConsultasVet::ConsultasVet(string umNomeVet): nomeVeterinario(umNomeVet),
		minhasConsultas(Consulta(0,0,0))
{}


bool Consulta::operator < (const Consulta &c2) const {
	if(mes == c2.getMes())
		if(dia==c2.getDia())
			return hora < c2.getHora();
		else
			return dia < c2.getDia();
	else
		return mes<c2.getMes();
}

bool Veterinario::operator<(const Veterinario& v1) const
{
	if(meusAnimais.size()==v1.getAnimais().size())
		return nome > v1.getNome();
	else
		return meusAnimais.size()>v1.getAnimais().size();
}

