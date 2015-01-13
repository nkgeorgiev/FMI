//============================================================================
// Name : prog1.cpp
// Author :
// Version :
// Copyright : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <stack>
#include <deque>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void prog1() {
	list<int> plates;
//input
	int a;
	do {
		cin >> a;
		if (a != 0)
			plates.push_back(a);
	} while (a != 0);
	vector<deque<int> > stream;
	int i = 0;
	list<int>::iterator it = plates.begin();
	stream.push_back(deque<int>(1, *it));
	it++;
//first iteration
	for (; it != plates.end(); it++) {
		if (*it > stream.back().back()) {
			stream.back().push_back(*it);
		} else {
			stream.push_back(deque<int>(1, *it));
		}
	}
//next iterations
	bool change = false;
	do {
		change = false;
		int idx;
		for (int i = 0; i < stream.size(); i++) {
			for (int j = i + 1; j < stream.size(); j++) {
				if (stream[i].back() < stream[j].front()) {
					stream[j].insert(stream[j].begin(), stream[i].begin(),
							stream[i].end());
					change = true;
					stream.erase(stream.begin() + i);
				}
			}
		}
	} while (change);
	for (int i = 0; i < stream.size(); i++) {
		cout << "Купчина " << i + 1 << ": ";
		for (int j = 0; j < stream[i].size(); j++) {
			cout << stream[i][j] << ' ';
		}
		cout << endl;
	}
}
int main() {
	prog1();
	return 0;
}
