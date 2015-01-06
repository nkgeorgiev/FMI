//============================================================================
// Name        : Graph.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	Graph g("file3.txt");
	g.printGraph();
	cout << "number of deadends: " << g.deadends() << endl;
	vector<int> v = g.shortestPath(1, 6);
	vector<int> a(1, 4);
	vector<int> c = g.alternativeRoutes(1, 6, a);
	cout << "shortest path: ";
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
	cout << endl;
	cout << "Contains cycle: " << g.containsCycle(7) << endl;
	vector<int> l = g.eulerianCircuit();
	cout << "lsize " << l.size() << endl;
	cout << "Eulerian Circuit: ";
	for (int i = 0; i < l.size(); i++)
		cout << l[i] << ' ';
	cout << endl;
	return 0;
}
