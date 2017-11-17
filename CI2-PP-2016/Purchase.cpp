/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"
#include <iterator>

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article* art = new Article(client,barCode);

	art->setPresent(present);
	art->setDeliverHome(deliverHome);

	return art;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	if(bags.size()==0){
		stack<Article*> s1;
		bags.push_back(s1);
	}

	if(bags.back().size()==Purchase::BAG_SIZE){
		stack<Article*> s1;
		bags.push_back(s1);
	}

	bags.back().push(article);
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	stack<Article*> st;

	list<stack<Article*> >::iterator it;

	for(it=bags.begin();it!=bags.end();it++){
		while(!it->empty()){
			if (it->top()->getPresent())
				presents.push_back(it->top());
			else
				st.push(it->top());
			it->pop();
		}

		while(!st.empty()){
			it->push(st.top());
			st.pop();
		}
	}


	return presents;

}

