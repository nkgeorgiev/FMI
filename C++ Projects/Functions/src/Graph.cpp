/*
 * Graph.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: nikolay
 */
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <queue>
#include <iostream>

using namespace std;



template<typename T>
class Graph {
private:
	map<T, int> mapping;
	map<int, T> reverse_mapping;
	vector<vector<bool> > matrix;
	int idx;

	void resize(int size) {
		if (idx >= matrix.size()) {
			matrix.resize(size, vector<bool>(size, false));
			for (int i = 0; i < matrix.size(); i++)
				matrix[i].resize(size, false);
		}
	}

	vector<int> neighbours(int v) {
		vector<int> n;
		for (int i = 0; i < matrix[v].size(); i++) {
			if (matrix[v][i] == true)
				n.push_back(i);
		}

		return n;
	}
	bool has_cycle(int v) {
		if (v < 0 || v >= matrix.size()) {
			return false;
		}
		//обхождаме графа с DFS и ако срещнем някъв началния връх
		//значи съществува цикъл
		vector<bool> visited(matrix.size(), false);
		stack<int> s;
		visited[v] = true;
		vector<int> n = neighbours(v);
		//рекурсия
//		if(n.size() == 0 && n[0] == v)
//			return false;
		for (int i = 0; i < n.size(); i++)
			s.push(n[i]);
		while (!s.empty()) {
			int u = s.top();
			s.pop();
			if (u == v)
				return true;
			if (!visited[u]) {
				visited[u] = true;
				n = neighbours(u);
				for (int i = 0; i < n.size(); i++)
					s.push(n[i]);
			}
		}
		return false;
	}

	void remove_cycles() {
		/*
		 * МЕТОДА ТРИЕ ВЪРХОВЕ!!!
		 */
			for(int i = 0; i < matrix.size();i++){
				if(has_cycle(i)){
					for(int j = 0; j < matrix[i].size(); j++)
						matrix[i][j] = false;
				}
			}
		}

	bool has_incoming_edges(int v){
		for(int i =0; i <matrix[v].size(); i++)
			if(matrix[i][v] == true) return true;
		return false;
	}

public:
	Graph() :
			idx(0) {
		//matrix.resize(10, vector<bool>(10, false));
	}
	void add_Edge(T f, T s) {
		if (mapping.find(f) == mapping.end()) {
			reverse_mapping[idx] = f;
			mapping[f] = idx++;
		}
		if (mapping.find(s) == mapping.end()) {
			reverse_mapping[idx] = s;
			mapping[s] = idx++;
		}
		resize(idx);
		int i = mapping[f], j = mapping[s];
		matrix[i][j] = true;
	}

	void remove_edge(T f, T s) {
		int i = mapping[f], j = mapping[s];
		matrix[i][j] = false;
	}
	vector<T> topologicalSort(){
		Graph g(*this);
		g.remove_cycles();
		vector<T> sorted;
		queue<int> S;
		for(int i = 0; i < g.matrix.size(); i++)
			if(!g.has_incoming_edges(i))
				S.push(i);

		while(!S.empty()){
			int node = S.front();
			S.pop();
			sorted.push_back(reverse_mapping[node]);
			vector<int> n = g.neighbours(node);
			for(int i = 0; i < n.size(); i++){
				g.remove_edge(reverse_mapping[node], reverse_mapping[i]);
				if(!g.has_incoming_edges(i))
					S.push(i);
			}
		}
		return sorted;








		return sorted;
	}


	void print() {
		for (int i = 0; i < matrix.size(); i++) {
			cout << reverse_mapping[i] << " | ";
			for (int j = 0; j < matrix[i].size(); ++j) {
				cout << matrix[i][j] << ' ';
			}
			cout << endl;
		}

	}

}
;

