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

#include "Graph.cpp"
#include "Function.h"

typedef shared_ptr<Function> func_ptr;

class FunctionOrder {
	map<string, func_ptr> functions;
	string text;
	vector<string> file;
	Graph<func_ptr> g;

	string getFunctionText(string);
	void loadFile(string);

	vector<func_ptr> findFunctionCalls(func_ptr);
public:

	FunctionOrder(string);
	void orderFunctions();

};

#endif /* FUNCTIONORDER_H_ */
