/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;


unsigned Jogo::numPalavras(string frase)
{
	if ( frase.length() == 0 ) return 0;
	int n=1;
	int pos = frase.find(' ');
	while ( pos != string::npos ) {
		frase = frase.substr(pos+1);
		pos = frase.find(' ');
		n++;
	}
	return n;
}


Jogo::Jogo()
{
}

Jogo::Jogo(list<Crianca>& lc2)
{
	criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
}


string Jogo::escreve() const
{
	string res;

	for(list<Crianca>::const_iterator it=criancas.begin();it!=criancas.end();it++)
		res+=it->escreve() + "\n";

	return res;
}


Crianca& Jogo::perdeJogo(string frase)
{
	int nPalavras = numPalavras(frase);
	int cnt=1;
	int cnt2=1;
	list<Crianca>::iterator it=criancas.begin();

	while(criancas.size()>1){
		if(cnt==nPalavras){
			criancas.erase(it);
			cnt=1;
			continue;
		}

		if(cnt2==criancas.size()){
			it=criancas.begin();
			cnt2=1;
			continue;
		}

		cnt++;
		it++;
		cnt2++;
	}


	return *(criancas.begin());

}


list<Crianca>& Jogo::inverte()
{
	/* This also works but isn't needed...
	list<Crianca>::iterator it=criancas.end();
	list<Crianca>::iterator it2=criancas.begin();
	it--;

	while(it2!=criancas.end()){
		it2 = criancas.insert(it2,*it);
		criancas.pop_back();

		it--;
		it2++;
	}
	*/

	criancas.reverse();

	return criancas;
}


list<Crianca> Jogo::divide(int id)
{
	list<Crianca> res;

	for(list<Crianca>::iterator it=criancas.begin();it!=criancas.end();it++)
	{
		if(it->getIdade()>id){
			res.push_back(*it);
			criancas.erase(it);
			it--;
		}
	}

	return res;
}



void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	for(list<Crianca>::const_iterator it=l1.begin();it!=l1.end();it++)
	{
		criancas.push_back(*it);
	}
}


bool Jogo::operator==(Jogo& j2)
{

	if(criancas == j2.getCriancasJogo())
		return true;

	return false;

}


bool existe(vector<int> v, int n)
{
	for(int i=0;i<v.size();i++)
		if(n==v.at(i))
			return true;

	return false;
}

list<Crianca> Jogo::baralha() const
{
	list<Crianca> res;
	vector<int> pos;
	int cnt=0;
	int cnt2=0;
	list<Crianca>::const_iterator it=criancas.begin();


	while(pos.size()!=criancas.size()){
		int randNum = rand()%criancas.size();
		if(!existe(pos,randNum)){
			pos.push_back(randNum);
		}
	}

	while(res.size()!=criancas.size()){
		for(int i=0;i<pos.size();i++)
			if(pos.at(i)==cnt){
				while(cnt2<i){
					it++;
					cnt2++;
				}
				cnt2=0;
				res.push_back(*it);
				it=criancas.begin();
				cnt++;
				break;
			}
	}

	return res;
}
