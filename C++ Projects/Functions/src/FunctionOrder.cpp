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
	while(!t.empty()){
		Function* f =  new Function(t);
		f->prettyPrint(cout);
		functions[f->getName()] = shared_ptr<Function>(f);
		t = getFunctionText(text.substr(text.find(t)+t.size()));
	}

}

FunctionOrder::~FunctionOrder(){
//	while(!functions.empty()){
//		Function* tmp = functions.back();
//		delete tmp;
//		functions.pop_back();
//	}

}
