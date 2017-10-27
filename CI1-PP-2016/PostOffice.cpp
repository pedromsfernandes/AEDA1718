/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}


Postman PostOffice::addMailToPostman(Mail *m, string name)
{
    for(int i=0;i<postmen.size();++i)
        if(postmen.at(i).getName()==name){
            postmen.at(i).addMail(m);
            return postmen.at(i);
        }

    throw NoPostmanException(name);
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance)
{
    unsigned int b=0;
    vector<Mail *> sendOther;

    for(int i=0;i<mailToSend.size();++i)
    {
        b+=mailToSend.at(i)->getPrice();
        Mail* temp = mailToSend.at(i);

        if(mailToSend.at(i)->getZipCode()>firstZipCode && mailToSend.at(i)->getZipCode()<lastZipCode)
            mailToDeliver.push_back(temp);
        else
            sendOther.push_back(temp);
    }

    balance=b;
    mailToSend.erase(mailToSend.begin(),mailToSend.end());
    mailToSend.clear();

    return sendOther;
}

vector<Mail *> PostOffice::removePostman(string name)
{
    vector<Mail*> mail;

    for(int i=0;i<postmen.size();++i)
        if(postmen.at(i).getName()==name){

            mail = postmen.at(i).getMail();
            postmen.erase(postmen.begin()+i);
            return mail;
        }

    return mail;
}

