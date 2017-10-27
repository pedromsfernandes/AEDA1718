/*
 * Mail.cpp
 */

#include "Mail.h"

Mail::Mail(string send, string rec, string zcode):
			sender(send),receiver(rec), zipCode(zcode)
{ }

Mail::~Mail()
{ }

string Mail::getZipCode() const {
	return zipCode;
}

RegularMail::RegularMail(string send, string rec, string zcode, unsigned int w):
			Mail(send, rec, zcode), weight(w)
{ }

GreenMail::GreenMail(string send, string rec, string zcode, string t):
			Mail(send, rec, zcode), type(t)
{ }

unsigned int RegularMail::getPrice () const
{
    unsigned int value;

    if(weight<=20)
        value=50;
    else if(weight<=100)
        value=75;
    else if(weight<=500)
        value=140;
    else
        value=325;

    return value;
}


unsigned int GreenMail::getPrice () const
{
    unsigned int value;

    if(type=="envelope")
        value=80;
    else if(type=="bag")
        value=200;
    else
        value=240;

    return value;
}







