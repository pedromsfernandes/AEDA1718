/*
 * Film.cpp
 */
#include "Film.h"


Film::Film(string tit, list<string> a): title(tit), actors(a)
{}

Film::Film(string tit): title(tit)
{}

Film::~Film()
{ }

string Film::getTitle() const
{ return title; }

list<string> Film::getActors() const
{ return actors; }

void Film::addActor(string actorName)
{ actors.push_back(actorName); }

bool Film::operator==(const Film &f1) const{
	return title==f1.getTitle();
}

bool Film::actorExists(string actor) const{

	for(list<string>::const_iterator it=actors.begin();it!=actors.end();it++)
		if((*it)==actor)
			return true;

	return false;
}
