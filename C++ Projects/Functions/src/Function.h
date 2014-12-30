/*
 * Function.h
 *
 *  Created on: Dec 27, 2014
 *      Author: nikolay
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

vector<string> split(string s, string delim);


class Function {
private:
	string name;
	string declaration;
	string contents;



	void readFunction(string);
public:
	Function(string);

//	const vector<string>& getArgs() const {
//		return args;
//	}
//
//	const vector<string>& getArgsType() const {
//		return args_type;
//	}



	const string& getName() const {
		return name;
	}

//	const string& getRetType() const {
//		return ret_type;
//	}

	void prettyPrint(ostream &)const;

	const string& getContents() const {
		return contents;
	}

	const string& getDeclaration() const{
		return declaration;
	}
};

#endif /* FUNCTION_H_ */
