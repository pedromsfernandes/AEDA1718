/*
 * exceptions.h
 *
 *  Created on: Nov 11, 2016
 *      Author: arocha
 */

#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <string>
using namespace std;

// a alterar
class FilaVazia {
public:
	FilaVazia() {
	}
	string getMsg() const {
		return "Fila Vazia";
	}
};


#endif /* SRC_EXCEPTIONS_H_ */
