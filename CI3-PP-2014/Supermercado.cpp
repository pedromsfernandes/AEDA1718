/*
 * Supermercado.cpp
 *
 * Created on: Dec 3, 2014
 *
 */

#include "Supermercado.h"
#include <iterator>
#include <utility>
#include <map>
//A ser implementado pelo estudante!


int Cesto::numItens() const
{
	return itens.size();
}

int Cesto::valor() const
{
	int sum=0;
	stack<Item> st;
	stack<Item> itens1=itens;

	while(!itens1.empty()){
		sum+=itens1.top().preco;
		itens1.pop();
	}

	return sum;
}

int Cliente::numeroItens() const
{
	int sum=0;

	for(list<Cesto>::const_iterator it=cestos.begin();it!=cestos.end();it++)
		sum+=it->numItens();

	return sum;
}

int Cliente::valorItens() const
{
	int sum=0;

	for(list<Cesto>::const_iterator it=cestos.begin();it!=cestos.end();it++)
		sum+=it->valor();

	return sum;
}

int Cesto::trocarItem(Item& novoItem){

	stack<Item> st;
	int c=0;

	while(!itens.empty()){

		if(itens.top().produto==novoItem.produto && itens.top().preco>novoItem.preco){
			st.push(novoItem);
			c++;
		}
		else{
			st.push(itens.top());
		}

		itens.pop();
	}

	itens=st;

	return c;

}

int Cliente::trocarItem(Item& novoItem){

	int c=0;

	for(list<Cesto>::iterator it=cestos.begin();it!=cestos.end();it++){
		c+=it->trocarItem(novoItem);
	}

	return c;

}

bool Item::operator<(const Item &i1){
	return peso>i1.peso;
}


void Cesto::organizarCesto(){

	vector<Item> v;

	while(!itens.empty()){
		v.push_back(itens.top());
		itens.pop();
	}

	sort(v.begin(),v.end());

	for(int i=0;i<v.size();i++){
		itens.push(v.at(i));
	}

}

void Cliente::organizarCestos(){

	for(list<Cesto>::iterator it=cestos.begin();it!=cestos.end();it++){
		it->organizarCesto();
	}
}


int Cesto::getVolume() const
{
	stack<Item> temp = itens;
	int sum=0;

	while(!temp.empty()){
		sum+=temp.top().volume;
		temp.pop();
	}

	return sum;
}

int Cesto::getPeso() const
{
	stack<Item> temp = itens;
	int sum=0;

	while(!temp.empty()){
		sum+=temp.top().peso;
		temp.pop();
	}

	return sum;
}


int Cesto::novoItem(const Item& umItem)
{
	if(getVolume()+umItem.volume>max_volume || getPeso()+umItem.peso>max_peso)
		return 0;

	itens.push(umItem);

	return itens.size();
}

int Cliente::novoItem(const Item& umItem)
{
	for(auto it=cestos.begin();it!=cestos.end();it++){
		if(it->novoItem(umItem)!=0)
			return cestos.size();
	}

	cestos.push_back(Cesto());

	auto it=cestos.end();
	it--;
	it->novoItem(umItem);

	return cestos.size();
}

vector<string> Cliente::contarItensPorTipo(){

	vector<string> v;
	stack<Item> itens;
	map<string,unsigned int> m;


	for(list<Cesto>::iterator it=cestos.begin();it!=cestos.end();it++){

		itens = it->getItens();
		while(!itens.empty()){
			if(m.empty()|| m.find(itens.top().tipo)==m.end()){
				m.insert(pair<string, unsigned int> (itens.top().tipo,1));
			}else if(m.find(itens.top().tipo)!=m.end()){
				m.at(itens.top().tipo)++;
			}

			itens.pop();
		}
	}

	for(map<string,unsigned int>::iterator it=m.begin();it!=m.end();it++){
		string s;
		s=it->first + " " + to_string(it->second);
		v.push_back(s);
	}


	return v;

}

int Supermercado::novoCliente(Cliente& umCliente){

	if(umCliente.getIdade()<65)
		filaNormal.push(umCliente);
	else{
		if(filaNormal.size()<filaPrioritaria.size())
			filaNormal.push(umCliente);
		else
			filaPrioritaria.push(umCliente);
	}

	return filaNormal.size()+filaPrioritaria.size();
}


Cliente Supermercado::sairDaFila(string umNomeDeCliente)
{
	queue<Cliente> temp1;
	queue<Cliente> temp2;
	Cliente c1;

	while(!filaNormal.empty()){
		if(filaNormal.front().getNome()!=umNomeDeCliente)
			temp1.push(filaNormal.front());
		else
			c1=filaNormal.front();
		filaNormal.pop();
	}

	filaNormal=temp1;

	if(c1.getIdade()!=0){
		return c1;
	}

	while(!filaPrioritaria.empty()){
		if(filaPrioritaria.front().getNome()!=umNomeDeCliente)
			temp2.push(filaPrioritaria.front());
		else
			c1=filaPrioritaria.front();
		filaPrioritaria.pop();
	}

	filaPrioritaria=temp2;


	if(c1.getIdade()!=0){
		return c1;
	}

	throw ClienteInexistente(umNomeDeCliente);
}
