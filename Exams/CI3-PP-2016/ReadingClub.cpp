/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"
#include <iterator>

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
		records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {

	BookCatalogItem notFound("", "", 0);

	for(int i=0;i<books.size();i++){
		BookCatalogItem c(books.at(i)->getTitle(),books.at(i)->getAuthor(), books.at(i)->getYear());
		BookCatalogItem f = catalogItems.find(c);

		if(f==notFound){
			c.addItems(books.at(i));
			catalogItems.insert(c);
		}
		else{
			catalogItems.remove(f);
			f.addItems(books.at(i));
			catalogItems.insert(f);
		}
	}
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;

	BookCatalogItem notFound("", "", 0);
	BookCatalogItem c(book->getTitle(), book->getAuthor(),book->getYear());

	BookCatalogItem f = catalogItems.find(c);

	vector<Book*> items = f.getItems();

	for(int i=0;i<items.size();i++){
		if(items.at(i)->getReader()==NULL)
			temp.push_back(items.at(i));
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {

	BookCatalogItem b(book->getTitle(),book->getAuthor(),book->getYear());

	BookCatalogItem f = catalogItems.find(b);
	vector<Book*> items = f.getItems();
	for(int i=0;i<items.size();i++){
		if(items.at(i)->getReader()==NULL){
			items.at(i)->setReader(reader);
			reader->addReading(book->getTitle(),book->getAuthor());

			catalogItems.remove(f);
			f.setItems(items);
			catalogItems.insert(f);

			return true;
		}
	}

	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {

	userRecords.insert(user);

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {

	vector<UserRecord> records = getUserRecords();

	for(int i=0;i<records.size();i++)
		if(records.at(i).getEMail()==user->getEMail())
			records.at(i).setEMail(newEMail);

	setUserRecords(records);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {

	for(int i=0;i<candidates.size();i++){
		if(candidates.at(i).numReadings()>=min)
			readerCandidates.push(candidates.at(i));
	}

}

int ReadingClub::awardReaderChampion(User& champion) {


	if(readerCandidates.empty())
		return 0;

	vector<User> users;

	users.push_back(readerCandidates.top());
	readerCandidates.pop();
	users.push_back(readerCandidates.top());
	readerCandidates.push(users.at(0));

	if(users.at(1)==users.at(0))
		return 0;
	else
	{
		champion=users.at(0);
		return readerCandidates.size();
	}
}
























