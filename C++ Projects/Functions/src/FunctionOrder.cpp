/*
 * Function.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: nikolay
 */

#include "FunctionOrder.h"
template<typename T>
void wtd(){
	list<T> i;
	typename list<T>::iterator it;



}
string FunctionOrder::getFunctionText(string t) {
	int f = -1, s = -1;
	int cnt = 0;
	for (int i = 0; i < t.size(); i++) {
		if (t[i] == '{') {
			if (f == -1)
				f = i;
			cnt++;
		} else if (t[i] == '}') {
			cnt--;
			if (cnt == 0) {
				s = i;
				break;
			}
		}
	}
	//cout<<t.substr(0,s+1)<<endl;
	return t.substr(0,s+1);
}

void FunctionOrder::loadFile(string filename) {
	ifstream ifs(filename.c_str());
	string line;
	while (!ifs.eof()) {
		getline(ifs, line);
		file.push_back(line);
		int i = 0;
		if (line[0] != '#' && line.find("using") == string::npos) {
			int idx = line.find("//");
			if (idx == string::npos)
				text += line;
			else
				text += line.substr(0, idx);
		}

	}

	regex rx("(\\s)*;(\\s)*");
	regex rx2("(\\s)*,(\\s)*");
	regex rx3("(\\s)+");
	regex rx4("/\*.*\*/");
	//махаме интервалите покрай ';'
	text = regex_replace(text, rx, string("; "));
	//махаме интервалите покрай ,
	text = regex_replace(text, rx2, string(", "));
	//намаляме интервалите до 1
	text = regex_replace(text, rx3, string(" "));
	//махаме коментари
	text = regex_replace(text, rx4, string(""));


	//cout<<text<<endl;;
	//contents = split(text, ";");
	//	vector<string> tmp = split(text, ";");
	//	for (int i = 0; i < tmp.size(); i++) {
	//		//cout << tmp[i] << endl;
	//		int idx1 = tmp[i].find("{");
	//		int idx2 = tmp[i].rfind("}");
	//		if (idx1 != string::npos) {
	//			//contents.push_back(tmp[i].substr(0, idx1+1));
	//			if (idx2 > idx1) {
	//				contents.push_back(tmp[i].substr(idx1, idx2 - idx1 - 1));
	//				contents.push_back(tmp[i].substr(idx2,1));
	//
	//				contents.push_back(tmp[i].substr(idx2+1));
	//			}
	//			else if (idx2 != string::npos){
	//				contents.push_back(tmp[i].substr(idx2,1));
	//						contents.push_back(tmp[i].substr(idx2+1));
	//			}else
	//				contents.push_back(tmp[i].substr(0,idx1+1)+";");
	//		}
	//		else
	//			contents.push_back(tmp[i] + ";");
	//	}
	////
	//	for(int i = 0; i < contents.size();i++)
	//		cout<<contents[i]<<endl;

}
void tmp() {
	//pair<int, int> idxs = ddz(text);
	//	while (idxs.first < text.size()-2 && idxs.second < text.size()-1) {
	//		int f = idxs.first, s = idxs.second;
	//		cout << idxs.first << " " << idxs.second << endl;
	//		string name = "";
	//		for (int i = f; i <= s; i++)
	//			name += text[i];
	//		functions.push_back(new Function(name, f+1, s));
	//
	//		idxs = ddz(vector<string>(text.begin() + s+1, text.end()));
	//		idxs.first += s+1;
	//		idxs.second += s+1;
	//	}
	//	for (int i = 0; i < functions.size(); i++) {
	//		cout << functions[i]->getName()<<endl;;
	//
	//	}
}

FunctionOrder::FunctionOrder(string filename) {
	loadFile(filename);
	string t = getFunctionText(text);
	int i = 0;
	while(!t.empty()){
		func_ptr  f = func_ptr(new Function(t));
		//f->prettyPrint(cout);
		string key = f->getName();
		functions[key] = f;
		t = getFunctionText(text.substr(text.find(t)+t.size()));
	}
	functions["foo"]->prettyPrint(cout);
	map<string, func_ptr>::iterator it = functions.begin();
	for(;it != functions.end(); it++){
		//it->second->prettyPrint(cout);
		vector<func_ptr> func_calls = findFunctionCalls(it->second);
		for(int i = 0; i < func_calls.size(); i++){
			g.add_edge(it->second, func_calls[i]);
		}
	}
}

vector<func_ptr> FunctionOrder::findFunctionCalls(func_ptr f){
	vector<func_ptr> functionCalls;
	string text = f->getContents();
	text = text.substr(text.find("{")+1);
	int idx1, idx2;
	idx1 = text.find('(');
	idx2 = text.find(')');
	while(idx1 != string::npos && idx2 != string::npos){
		while(text[--idx1] == ' ');
		string name = text.substr(0,idx1+1);

		name = name.substr(name.find_last_of(" ;}")+1);
		//cout<<name<<endl;
		text = text.substr(idx2+1);
		idx1 = text.find('(');
		idx2 = text.find(')');
		//cout<<name<<endl;

		if(functions.find(name) != functions.end())
		{
			cout<<name<<endl;;
			functionCalls.push_back(functions.find(name)->second);
		}

	}


	return functionCalls;

}

void FunctionOrder::orderFunctions() {
	vector<func_ptr> sorted = g.topologicalSort();
	for(int  i = 0; i< sorted.size();i++){
		cout<<sorted[i]->getDeclaration()<<endl;;
	}
}
