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

bool isIn(string s, char c){
	for(int i = 0; i < s.size(); i++)
		if(s[i] == c) return true;
	return false;
}

vector<string> multi_split(string s, string delim){
	string cpy = s;
	vector<string> tokens;
	int start = 0;
	for(int i = 0; i < s.size(); i++){
		for(int j = 0; j < delim.size(); j++){
			if(isIn(s, delim[j])){
				tokens.push_back(s.substr(start, i - start+1));
				s = s.substr(i+1);
			}
		}
	}
	return tokens;
}


void Function::readFunction(string text){
	//text - сигнатурата - type name(args)
	int first_bracket = text.find('(');
	int second_bracket = text.find(')');
	string first = text.substr(0,first_bracket);
	string second = text.substr(first_bracket+1, second_bracket- first_bracket-1);
	//вземаме името и типа
	int end_idx = first.size()-1;
	while(first[end_idx--]==' ');
	int start_idx = end_idx;
	while(first[start_idx--] != ' ');
	this->name = first.substr(start_idx+2, end_idx-start_idx);
	this->ret_type = first.substr(0,start_idx+1);

	start_idx = first.size() + 2;
	end_idx = second.size() - 1;
	vector<string> arg = split(second, ",");
	for(int i = 0; i < arg.size(); i++){
		vector<string> v = split(arg[i], " ");
		args_type.push_back(v[0]);
		args.push_back(v[1]);
	}

}

Function::Function(string text){
	readFunction(text);
	contents = text;

}


void Function::prettyPrint() const{
	vector<string> tmp;
	string c = contents;
	int idx = c.find('{');
	tmp.push_back(c.substr(0,idx+1));
	c = c.substr(idx+1);
	while(!c.empty()){
		int a[3];
		a[0] = c.find('{');
		a[1] = c.find(';');
		a[2] = c.find('}');
		if(a[0]> a[1]){
			if(a[0] > a[2]){
				tmp.push_back(c.substr(0,a[0]+1));
				c = c.substr(a[0]+1);
			} else{
				tmp.push_back(c.substr(0,a[1]+1));
				c = c.substr(a[1]+1);
			}
		}
	}


	for(int i = 0; i < tmp.size(); i++)
		cout<<tmp[i]<<endl;

}


