/*
 * Postman.cpp
 */
#include "Postman.h"


Postman::Postman(): id(0) {}

unsigned int Postman::idCount = 0;

Postman::Postman(string name)
{
	idCount++;

    this->name=name;
    this->id=idCount;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &p2) const
{
    unsigned int counter1=1, counter2=1;

    if(myMail.size()==0)
        counter1=0;
    if(p2.getMail().size()==0)
        counter2=0;

    for(int i=0;i<myMail.size()-1;++i)
        if(myMail.at(i)->getZipCode()!=myMail.at(i+1)->getZipCode())
            counter1++;

    for(int i=0;i<p2.getMail().size()-1;++i)
        if(p2.getMail().at(i)->getZipCode()!=p2.getMail().at(i+1)->getZipCode())
            counter2++;

    if(counter1<counter2)
        return true;

    return false;

}

NoPostmanException::NoPostmanException(string name)
{
    this->name=name;
}

string NoPostmanException::getName() const
{
    return name;
}



