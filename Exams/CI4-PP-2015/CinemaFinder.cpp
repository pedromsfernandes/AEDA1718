/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	for(tabHFilm::const_iterator it = films.begin();it!=films.end();it++){
		if((*it).film->actorExists(actorName))
			res.push_back((*it).film->getTitle());
	}

	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	for(tabHFilm::iterator it = films.begin();it!=films.end();it++){
		if((*it).film->getTitle()==filmTitle){
			(*it).film->addActor(actorName);
			return;
		}
	}

	Film* temp = new Film(filmTitle);
	FilmPtr fp;
	fp.film=temp;

	films.insert(fp);

}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";

	priority_queue<Cinema> temp = cinemas;
	list<string> ser;

	while(!temp.empty()){
		ser = temp.top().getServices();
		for(list<string>::const_iterator it = ser.begin();it!=ser.end();it++){
			if(*it==service1)
				return temp.top().getName();
		}
		temp.pop();
	}

	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	if(cinemas.empty())
		throw CinemaNotFound();

	priority_queue<Cinema> temp = cinemas;

	while(!temp.empty()){
		Cinema cin = temp.top();

		if(cin.getDistance()<maxDistance){
			cin.addService(service1);
			temp.pop();
			temp.push(cin);
			cinemas=temp;
			return;
		}
		temp.pop();
	}

	throw CinemaNotFound();
}
