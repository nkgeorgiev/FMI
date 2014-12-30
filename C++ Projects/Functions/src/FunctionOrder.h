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
	map<string, shared_ptr<Function> > functions;
	string text;
	map<int, shared_ptr<Function> > mapping;;
	vector<vector<int> > graph;

	string getFunctionText(string);
	void loadFile(string);

	vector<shared_ptr<Function> > findFunctionCalls(string);
public:

	FunctionOrder(string);

};

#endif /* FUNCTIONORDER_H_ */
