/*
 * Article.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Article.h"


Article::Article(long cli, long bc) : client(cli), barCode(bc) {
	this->present = false;
	this->deliverHome = false;
	this->presentNumber = 0;
	this->arrivalNumber = 0;
};

long Article::getClient() const {
	return client;
}

long Article::getBarCode() const {
	return barCode;
}

bool Article::getPresent() const {
	return present;
}

void Article::setPresent(bool present) {
	this->present = present;
}

bool Article::getDeliverHome() const {
	return deliverHome;
}

void Article::setDeliverHome(bool deliverHome) {
	this->deliverHome = deliverHome;
}

int Article::getPresentNumber() const {
	return presentNumber;
}

void Article::setPresentNumber(int presentNumber) {
	this->presentNumber = presentNumber;
}

int Article::getArrivalNumber() const {
	return arrivalNumber;
}

void Article::setArrivalNumber(int arrivalNumber) {
	this->arrivalNumber = arrivalNumber;
}


bool Article::operator<(const Article &a1)
{
	if(deliverHome && a1.getDeliverHome())
		return arrivalNumber < a1.getArrivalNumber();
	else if(!deliverHome && a1.getDeliverHome())
		return true;
	else if (deliverHome && !a1.getDeliverHome())
		return false;
	else if (!deliverHome && !a1.getDeliverHome()){
		if(presentNumber+2 <a1.getPresentNumber())
			return true;
		else if(presentNumber > a1.getPresentNumber() +2)
			return false;
		else
			return arrivalNumber < a1.getArrivalNumber();
	}
}
