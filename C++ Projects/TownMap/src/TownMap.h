/*
 * Graph.h
 *
 *  Created on: Dec 21, 2014
 *      Author: nikolay
 */

#ifndef TOWNMAP_SRC_GRAPH_H_
#define TOWNMAP_SRC_GRAPH_H_

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

class TownMap {
private:
	vector<vector<int> > adjList;
	// чете граф от файл
	void loadTownMap(string);

	int minDist(set<int>, vector<int>);
	void DFSEuler(int, int, set<pair<int, int> >&, vector<int>&);
public:
	//конструктор с параметър име на файл
	TownMap(string);

	//конструктор с параметър списък на съседство
	TownMap(vector<vector<int> >);

	//връща съседите на даден връх
	vector<int> neighbours(int);

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

	//принтира графа
	void printTownMap();

};

#endif /* TOWNMAP_SRC_GRAPH_H_ */
