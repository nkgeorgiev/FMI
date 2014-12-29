/*
 * Function.h
 *
 *  Created on: Dec 27, 2014
 *      Author: nikolay
 */

#ifndef FUNCTIONORDER_H_
#define FUNCTIONORDER_H_

#include <fstream>
#include <regex>


#include "Function.h"


class FunctionOrder {
	vector<Function*> functions;
	string text;
	//vector<string> contents;

	string getFunctionText(string);
	void loadFile(string);
public:
	FunctionOrder(string);
	~FunctionOrder();

};

#endif /* FUNCTIONORDER_H_ */
