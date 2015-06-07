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

	return make_pair(-1, -1);
}

void FunctionOrder::loadFile(string filename) {
	ifstream ifs(filename.c_str());
	string line;
	int i = -1;
	while (!ifs.eof()) {
		getline(ifs, line);
		file.push_back(line);
	}
}

FunctionOrder::FunctionOrder(string filename) {
	this->filename = filename;
	loadFile(filename);
	pair<int, int> t = getFunctionText(file, 0, file.size());
	b = t.first;
	while (t.first >= 0) {
		func_ptr f = func_ptr(new Function(file, t.first, t.second));
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
		vector<func_ptr> func_calls = findFunctionCalls(it->second);
		for (int i = 0; i < func_calls.size(); i++) {
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
		name = name.substr(name.find_last_of(" ;}\t\n,") + 1);
		text = text.substr(idx2 + 1);
		idx1 = text.find('(');
		idx2 = text.find(')');

		if (functions.find(name) != functions.end()) {
			functionCalls.push_back(functions.find(name)->second);
		}

	}

	return functionCalls;

}

void FunctionOrder::orderFunctions() {
	ofstream ofs("new."+filename, ofstream::out);
	for (int i = 0; i < b; i++) {
		ofs << file[i] << endl;
	}
	vector<func_ptr> declarations = g.remove_cycles();
	vector<func_ptr> sorted = g.topologicalSort();
	for (int i = 0; i < declarations.size(); i++) {
		ofs << sorted[i]->getDeclaration()<<";\n";
	}
	ofs << endl;
	for (int i = sorted.size() - 1; i >= 0; i--) {
		for (int j = sorted[i]->getStart(); j <= sorted[i]->getEnd(); j++)
			ofs << file[j] << endl;
		ofs<<endl;
	}

	ofs.close();
}
