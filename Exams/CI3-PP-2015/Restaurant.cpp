/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <iostream>
#include <algorithm>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	Dish* temp = new Dish(collection,type);


	for(int i=0;i<n;i++)
		getCleanDishStack(collection,type).push(temp);

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d=dirty.front();

	dirty.pop();
	drying.push_back(d);

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	if(idx<0 || idx>=tables.size())
		return;

	vector<Dish*> v =tables.at(idx).clear();

	for(int i=0;i<v.size();i++)
		dirty.push(v.at(i));

}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	vector<Dish*> d;

	for(auto it=drying.begin();it!=drying.end();it++)
		if((*it)->getCollection()==collection && (*it)->getType()==type){
			d.push_back(*it);
			it=drying.erase(it);
			if(it!=drying.begin())
				it--;
		}

	addDishes(d.size(),collection,type);

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	if(idx<0 || idx>=tables.size())
		return;

	vector<Dish*> v;
	vector<stack<Dish*> > v2 = tables.at(idx).getPlaces();

	if(!tables.at(idx).empty())
		throw TableNotReadyException();

	for(int i=0;i<clean.size();i++){
		if(clean.at(i).top()->getCollection()==collection && clean.at(i).top()->getType()==0){

			if(clean.at(i).size()<v2.size()){
				throw NotEnoughDishesException();
			}

			while(v.size()<v2.size()){
				v.push_back(clean.at(i).top());
				clean.at(i).pop();
			}
			break;
		}
	}

	tables.at(idx).putOn(v);
}


/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	while(!drying.empty()){
		vector<Dish*> v;
		v.push_back(*drying.begin());
		drying.erase(drying.begin());
		for(auto it=drying.begin();it!=drying.end();it++)
			if(**it==**v.begin()){
				v.push_back(*it);
				it=drying.erase(it);
				if(it!=drying.begin())
					it--;
			}

		for(int i=0;i<v.size();i++)
			dry_grouped.push_back(v.at(i));
	}

	return dry_grouped;
}


bool exists(Dish* d, vector<stack<Dish*> >s){
	for(int i=0;i<s.size();i++)
		if(*s.at(i).top()==*d)
			return true;

	return false;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	int counter=1;
	bool passei=false;
	int c=0;
	list<Dish*> temp = grouped_dishes;
	list<Dish*>::iterator it = temp.begin();
	list<Dish*>::iterator it2 = it;
	it2++;

	while(it!=temp.end()){

		if(it2==temp.end()){
			addDishes(counter,(*it)->getCollection(),(*it)->getType());
			c++;
		}
		else if(**it==**it2){
			counter++;
		}
		else{
			addDishes(counter,(*it)->getCollection(),(*it)->getType());
			c++;
			counter=1;
		}

		it++;
		it2++;
	}

	return c;

}




