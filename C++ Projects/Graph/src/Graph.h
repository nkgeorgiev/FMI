/*
 * Graph.h
 *
 *  Created on: Dec 21, 2014
 *      Author: nikolay
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <set>
#include <stack>
#include <fstream>
#include <iostream>
#include <list>
#include <limits.h>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Graph {
private:
	vector<vector<int> > adjList;
	// чете граф от файл
	void loadGraph(string);

	vector<string> split(string, string);
	vector<int> neighbours(int);
	int minDist(set<int>, vector<int>);
	void DFSEuler(int, int, set<pair<int, int> >&, vector<int>&);
public:
	//конструктор с параметър име на файл
	Graph(string);

	//конструктор с параметър списък на съседство
	Graph(vector<vector<int> >);

	//намира най къс път между 2 върха
	vector<int> shortestPath(int, int);

	//проверява дали съществува път
	bool pathExists(int, int);

	//проверява дали има цикъл
	bool containsCycle(int);

	//извежда всички задънени улици
	int deadends();

	//намира ойлеров път
	vector<int> eulerianCircuit();

	//намира най-къс алтернативен маршрут
	vector<int> alternativeRoutes(int, int, vector<int>);

	//извежда списъка на съседство
	void printGraph();

};

#endif /* GRAPH_H_ */
