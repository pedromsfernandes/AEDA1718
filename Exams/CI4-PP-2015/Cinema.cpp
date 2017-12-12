/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
	if(distance==cr.getDistance())
		return services.size()<cr.services.size();
	else
		return distance>cr.getDistance();
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = NULL;
	BST<FilmTime> tempTable = timetable;

	while(!tempTable.isEmpty()){
		FilmTime temp = tempTable.findMax();

		if(temp.getHour()<h1){
			h1=temp.getHour();
			return temp.getFilm();
		}
		else if (temp.getHour()==h1){
			return temp.getFilm();
		}
		else{
			tempTable.remove(temp);
		}
	}


	return res;
}


//a2

bool Cinema::isRoomBusy(unsigned room, unsigned h) const{
	BSTItrIn<FilmTime> it(timetable);

	while(!it.isAtEnd()){

		FilmTime temp = it.retrieve();

		if(temp.getHour()==h && temp.getRoomID()==room)
			return true;

		it.advance();
	}

	return false;

}

bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {

	if(isRoomBusy(room1,h2))
		return false;

	BSTItrIn<FilmTime> it(timetable);

	while(!it.isAtEnd()){
		FilmTime temp = it.retrieve();
		if(temp.getRoomID()==room1 && temp.getHour()==h1){
			timetable.remove(temp);
			temp.setHour(h2);
			timetable.insert(temp);
			return true;
		}

		it.advance();
	}

	return false;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned counter=1;
	BSTItrIn<FilmTime> it(timetable);

	while(!it.isAtEnd()){
		FilmTime temp = it.retrieve();

		if(temp.getHour()==h1)
			counter++;

		it.advance();
	}

	if(counter<=numberOfRooms){
		FilmTime f(h1,f1,counter);
		timetable.insert(f);
		return counter;
	}
	else return 0;
}






