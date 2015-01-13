/*
 * Function.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: nikolay
 */

#include "Function.h"

vector<string> split(string s, string delim) {
	vector<string> tokens;
	int start = 0;
	int end = s.find(delim);
	while (end != string::npos) {
		string token = s.substr(start, end - start);
		if (token.size() > 0)
			tokens.push_back(token);
		start = end + delim.length();
		end = s.find(delim, start);

	}
	tokens.push_back(s.substr(start, end - start));
	return tokens;

}

void Function::readFunction(string text) {
	int first_bracket = text.find('(');
	int second_bracket = text.find(')');
	string first = text.substr(0, first_bracket);
	string second = text.substr(first_bracket + 1,
			second_bracket - first_bracket - 1);
	//вземаме името и типа
	int end_idx = first.size() - 1;
	while (first[end_idx--] == ' ')
		;
	int start_idx = end_idx;
	while (first[start_idx--] != ' ')
		;
	this->name = first.substr(start_idx + 2, end_idx - start_idx);
	this->declaration = text.substr(0, second_bracket+1);

}

Function::Function(string text) {
	readFunction(text);
	contents = text;

}

Function::Function(vector<string> v, int s, int e) {
	start = s;
	end = e;
	string text;
	for(int i = s; i <= e; i++)
		text +=v[i];
	readFunction(text);
	contents = text;
}


