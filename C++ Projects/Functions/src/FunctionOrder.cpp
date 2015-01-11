/*
 * Function.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: nikolay
 */

#include "FunctionOrder.h"

pair<int, int> FunctionOrder::getFunctionText(vector<string> v, int start,
		int end) {
	int f = -1, s = -1;
	int cnt = 0;
	for (int j = start; j < end; j++) {
		string t = v[j];
		for (int i = 0; i < t.size(); i++) {
			if (t[i] == '{') {
				if (f == -1)
					f = j;
				cnt++;
			} else if (t[i] == '}') {
				cnt--;
				if (cnt == 0) {
					s = j;
					return make_pair(f, s);
				}
			}
		}
	}
	//cout<<t.substr(0,s+1)<<endl;
//	vector<string> tmp(v.begin()+f, v.begin() + s);
//	string text;
//	for(int i = 0; i < tmp.size(); i++)
//		text += tmp[i];
//	return text;
	return make_pair(-1, -1);
}

void FunctionOrder::loadFile(string filename) {
	ifstream ifs(filename.c_str());
	string line;
	int i = -1;
	while (!ifs.eof()) {
		getline(ifs, line);
		file.push_back(line);

		//int i = 0;
		if (line[0] != '#' && line.find("using") == string::npos) {
			int idx = line.find("//");
//			if (idx == string::npos)
//				text += line;
//			else
//				text += line.substr(0, idx);
		}
		i++;
	}

//	regex rx("(\\s)*;(\\s)*");
//	regex rx2("(\\s)*,(\\s)*");
//	regex rx3("(\\s)+");
//	regex rx4("/\*.*\*/");
//	//махаме интервалите покрай ';'
//	text = regex_replace(text, rx, string("; "));
//	//махаме интервалите покрай ,
//	text = regex_replace(text, rx2, string(", "));
//	//намаляме интервалите до 1
//	text = regex_replace(text, rx3, string(" "));
//	//махаме коментари
//	text = regex_replace(text, rx4, string(""));

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

FunctionOrder::FunctionOrder(string filename) {
	this->filename = filename;
	loadFile(filename);
	pair<int, int> t = getFunctionText(file, 0, file.size());
	b = t.first;
	while (t.first >= 0) {
		func_ptr f = func_ptr(new Function(file, t.first, t.second));
		//f->prettyPrint(cout);
		string key = f->getName();
		functions[key] = f;
		t = getFunctionText(file, t.second + 1, file.size());
	}
	vector<func_ptr> tmp;
	map<string, func_ptr>::iterator it = functions.begin();
	while (it != functions.end()) {
		tmp.push_back(it->second);
		it++;
	}
	g = Graph<func_ptr>(tmp);

	it = functions.begin();
	for (; it != functions.end(); it++) {
		//it->second->prettyPrint(cout);
		vector<func_ptr> func_calls = findFunctionCalls(it->second);
		for (int i = 0; i < func_calls.size(); i++) {
			//if (it->second == func_calls[i])
				g.add_edge(it->second, func_calls[i]);
		}
	}
}

vector<func_ptr> FunctionOrder::findFunctionCalls(func_ptr f) {
	vector<func_ptr> functionCalls;
	string text = f->getContents();
	text = text.substr(text.find("{") + 1);
	int idx1, idx2;
	idx1 = text.find('(');
	idx2 = text.find(')');
	while (idx1 != string::npos && idx2 != string::npos) {
		while (text[--idx1] == ' ') {
		}
		string name = text.substr(0, idx1 + 1);
		int a = name.find_last_of(" ;}") + 1;
		int b = name.find_last_of("\s") + 1;
		name = name.substr(name.find_last_of(" ;}\t\n,") + 1);
		//cout<<name<<endl;
		text = text.substr(idx2 + 1);
		idx1 = text.find('(');
		idx2 = text.find(')');
		//cout<<name<<endl;

		if (functions.find(name) != functions.end()) {
			//if (functions.find(name)->second != f)
			functionCalls.push_back(functions.find(name)->second);
		}

	}

	return functionCalls;

}

void FunctionOrder::orderFunctions() {
	for (int i = 0; i < b; i++) {
		cout << file[i] << endl;
	}
	vector<func_ptr> declarations = g.topologicalSort().first;
	vector<func_ptr> sorted = g.topologicalSort().second;
	for (int i = 0; i < declarations.size(); i++) {
		cout << sorted[i]->getDeclaration() << ';' << endl;
	}
	cout << "pff" << endl;
	for (int i = sorted.size() - 1; i >= 0; i--) {
		for (int j = sorted[i]->getStart(); j <= sorted[i]->getEnd(); j++)
			cout << file[j] << endl;
		cout<<endl;
	}
	cout << "ti eba maikata!!!" << endl;
}
