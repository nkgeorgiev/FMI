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
	unsigned int idx;

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

		vector<bool> visited(matrix.size(), false);
		stack<int> s;
		visited[v] = true;
		vector<int> n = neighbours(v);
		//рекурсия
		//if(n.size() == 1 && n[0] == v)
		//	return false;
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
					if (!visited[n[i]])
						s.push(n[i]);
			}
		}
		return false;
	}

	vector<T> remove_cycles() {

		vector<T> declarations(1);
		for (int i = 0; i < matrix.size(); i++) {
			if (has_cycle(i)) {
				declarations.push_back(reverse_mapping[i]);
				for (int j = 0; j < matrix[i].size(); j++)
					matrix[i][j] = false;
			}
		}
		return declarations;
	}

	bool has_incoming_edges(int v) {
		for (int i = 0; i < matrix[v].size(); i++)
			if (matrix[i][v] == true)
				return true;
		return false;
	}

public:
	Graph() :
			idx(0) {
	}

	Graph(const vector<T>& v) :
			idx(0) {
		resize(v.size());
		for (int i = 0; i < v.size(); i++) {
			reverse_mapping[idx] = v[i];
			mapping[v[i]] = idx++;
		}
	}

	//създаване на ребро между f и s
	void add_edge(T f, T s) {
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

	//триене на ребро между f и s (ако съществува)
	void remove_edge(T f, T s) {
		int i = mapping[f], j = mapping[s];
		matrix[i][j] = false;
	}

	pair<vector<T>, vector<T> > topologicalSort() {
		Graph g(*this);
		set<int> vertices;
		for (int i = 0; i < matrix.size(); i++) {
			vertices.insert(i);
		}

//		for (int i = 0; i < g.matrix.size(); i++) {
//			for (int j = 0; j < g.matrix[i].size(); j++) {
//				if (g.matrix[i][j] == true) {
//					sorted.push_back(reverse_mapping[i]);
//					break;
//				}
//			}
//		}
		vector<T> declarations = g.remove_cycles();
		//vector<T> sorted(declarations.begin(), declarations.end());
		vector<T> sorted;
		queue<int> S;
		for (int i = 0; i < g.matrix.size(); i++)
			if (!g.has_incoming_edges(i))
				S.push(i);

		while (!S.empty()) {
			int node = S.front();
			S.pop();
			sorted.push_back(reverse_mapping[node]);
			vertices.erase(node);
			vector<int> n = g.neighbours(node);
			for (int i = 0; i < n.size(); i++) {
				g.remove_edge(reverse_mapping[node], reverse_mapping[n[i]]);
				if (!g.has_incoming_edges(n[i])) {
					S.push(n[i]);
					//vertices.insert(n[i]);
				}
			}
		}
		//g.print();
		set<int>::iterator it = vertices.begin();
		//sorted.insert(0,*it++);
		while (it != vertices.end()) {
			sorted.insert(sorted.begin(), reverse_mapping[*it]);
			it++;
		}

		return make_pair(declarations, sorted);
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

