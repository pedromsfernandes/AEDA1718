
#include "Cooperativa.h"
#include <sstream>

//TODO: Implementar corretamente o construtor e inicializacao da BST!
Cooperativa::Cooperativa():vinhos(Vinho("",0))
{}

void Cooperativa::addVinhos(const vector<Vinho>& vv){
	for(int i=0;i<vv.size();i++){
		vinhos.insert(vv.at(i));
	}
}

bool Vinho::operator<(const Vinho& v1) const{
	if(ano==v1.getAno())
		return nome<v1.getNome();
	else
		return ano>v1.getAno();
}

bool Vinho::operator==(const Vinho& v1) const{
	return nome == v1.getNome();
}

bool Vinicola::operator<(const Vinicola& v1) const{
	if(vinhos == v1.getVinhos())
		return nome>v1.getNome();
	else
		return vinhos > v1.getVinhos();
}

bool Enologo::operator<(const Enologo& e1) const{
	return getNumVinhos() < e1.getNumVinhos();
}

int Enologo::getNumVinhos() const{

	int counter=0;

	for(list<Vinicola>::const_iterator it=vinicolas.begin();it!=vinicolas.end();it++){
		counter+=it->getVinhos();
	}

	return counter;
}

list<Vinicola>::iterator Enologo::getEnd(){
	return vinicolas.end();
}

list<Vinicola>::iterator Enologo::existsVinicola(string umaVinicola){

	for(list<Vinicola>::iterator it=vinicolas.begin();it!=vinicolas.end();it++){
			if(it->getNome()==umaVinicola)
				return it;
		}

	return vinicolas.end();
}
list<string> Cooperativa::vinhosDisponiveis(int ano1, int ano2){
	list<string> names;

	BST<Vinho> temp = vinhos;

	while(!temp.isEmpty()){
		Vinho v = temp.findMin();
		string inf, inf2;
		ostringstream oss;

		if(v.getAno()>=ano1 && v.getAno()<=ano2){
			oss << v.getAno();
			inf2 = oss.str();
			inf=v.getNome() + " " + inf2;
			names.push_back(inf);
		}

		temp.remove(v);
	}

	names.sort();
	names.reverse();

	if(names.size()==0)
		names.push_back("Indisponivel");

	return names;
}

int Cooperativa::delVinhoNome(string umVinho){
	int counter=0;

	Vinho v(umVinho);
	Vinho temp;
	BSTItrIn<Vinho> it(vinhos);

	while(!it.isAtEnd()){
		temp = it.retrieve();

		if(temp == v){
			counter++;
			vinhos.remove(temp);
		}

		it.advance();
	}


	return counter;
}

void Cooperativa::addVinicola(string umaVinicola){

	for(hashVinicola::iterator it=vinicolas.begin();it!=vinicolas.end();it++){
		if(it->getNome()==umaVinicola){
			Vinicola temp = (*it);
			vinicolas.erase(temp);
			temp.addVinho();
			vinicolas.insert(temp);
			return;
		}
	}

	Vinicola novo(umaVinicola);
	vinicolas.insert(novo);

}

Vinicola Cooperativa::maisOpcoes(){

	Vinicola v("ola");

	for(hashVinicola::iterator it=vinicolas.begin();it!=vinicolas.end();it++){
		if((*it)<v)
			v=(*it);
	}

	return v;
}

void Cooperativa::addEnologoVinicola(string umEnologo, string umaVinicola){


	if(enologos.empty()){
		Enologo e1(umEnologo);
		enologos.push(e1);
		return;
	}

	priority_queue<Enologo> temp = enologos;
	priority_queue<Enologo> novo;
	bool exists=false;

	while(!temp.empty()){
		Enologo e = temp.top();

		if(e.getNome()==umEnologo){
			list<Vinicola>::iterator it=e.existsVinicola(umaVinicola);

			if(it!=e.getEnd())
				it->addVinho();
			else{
				Vinicola v(umaVinicola);
				e.addVinicolaInexistente(umaVinicola);
			}
			exists=true;
		}

		novo.push(e);
		temp.pop();
	}

	if(!exists){
		Enologo e1(umEnologo);
		novo.push(e1);
	}

	enologos=novo;
}

list<Vinicola> Cooperativa::vinicolasMelhoresNEnologos(int n){

	priority_queue<Enologo> temp = enologos;
	list<Vinicola> vin;
	int counter = 0;

	while(!temp.empty() && counter<n){

		Enologo e = temp.top();
		list<Vinicola> mais = e.getVinicolas();
		for(list<Vinicola>::iterator it =mais.begin();it!=mais.end();it++){
			vin.push_back(*it);
		}
		temp.pop();
		counter++;
	}

	return vin;
}
