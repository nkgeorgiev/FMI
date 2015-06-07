/*
 * TownMap.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: nikolay
 */

#include "TownMap.h"

bool isIn(int x, vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == x)
			return true;
	}
	return false;
}

template<typename T>
bool allSame(T x, vector<T> v) {
	for (int i = 0; i < v.size(); i++)
		if (v[i] != x)
			return false;
	return true;
}

vector<string> split(string s, string delim) {
	vector<string> tokens;
	int start = 0;
	int end = s.find(delim);
	while (end != string::npos) {
		string token = s.substr(start, end - start);
		if (token.size() > 0)
			tokens.push_back(token);
		start = end + delim.length();
		end = s.find(delim, start);

	}
	tokens.push_back(s.substr(start, end - start));
	return tokens;

}

int TownMap::minDist(set<int> s, vector<int> dist) {
	set<int>::iterator iter = s.begin();
	int m = *iter;
	for (; iter != s.end(); iter++) {
		if (dist[*iter] < m)
			m = *iter;
	}
	return m;
}

vector<int> TownMap::neighbours(int v) {
	vector<int> n;
	for (int i = 0; i < adjList[v].size(); i++) {
		if (adjList[v][i] > 0)
			n.push_back(i);
	}

	return n;
}

TownMap::TownMap(string name) {
	loadTownMap(name);

}

TownMap::TownMap(vector<vector<int> > l) {
	adjList = l;
}

void TownMap::loadTownMap(string name) {
	ifstream ifs(name.c_str());
	string line;
	//i - first vertex
	//j - second vertex
	//w - weight
	unsigned int i, j, w;
	while (!ifs.eof()) {
		getline(ifs, line);
		vector<string> tokens = split(line, " ");
		i = atoi(tokens[0].c_str());
		//resize the outer vector if needed
		if (i >= adjList.size())
			adjList.resize(i + 1);

		for (int idx = 1; idx < tokens.size(); idx += 2) {
			j = atoi(tokens[idx].c_str());
			w = atoi(tokens[idx + 1].c_str());

			if (j >= adjList[i].size()) {
				adjList[i].resize(j + 1);
				if (j >= adjList.size())
					adjList.resize(j + 1);
			}
			adjList[i][j] = w;
		}
	}
}

vector<int> TownMap::shortestPath(int begin, int end) {
	/*
	 * begin - начален връх
	 * end - краен връх
	 */
	if (begin <= 0 || begin >= adjList.size() || end <= 0
			|| end >= adjList.size())
		return vector<int>();
	//инициализация
	set<int> q;
	for (int i = 1; i < adjList.size(); i++)
		q.insert(i);
	vector<int> dist(adjList.size(), INT_MAX);
	vector<int> previous(adjList.size(), NULL);
	dist[begin] = 0;

	while (!q.empty()) {
		int u = minDist(q, dist);
		q.erase(u);

		vector<int> n = neighbours(u);
		for (int i = 0; i < n.size(); i++) {
			int v = n[i];
			int alt = dist[u] + adjList[u][v];
			if (alt < dist[v]) {
				dist[v] = alt;
				previous[v] = u;
			}
		}
		if (u == end)
			break;
	}

	//generate the path from start to end
	vector<int> s;
	int u = end;
	while (previous[u] != NULL) {
		s.push_back(u);
		u = previous[u];
	}
	s.push_back(begin);
	reverse(s.begin(), s.end());
	return s;

}

int TownMap::deadends() {
	int cnt = 0;
	for (int i = 1; i < adjList.size(); i++) {
		if (allSame(0, adjList[i]))
			cnt++;
	}
	return cnt;
}

bool TownMap::pathExists(int v, int u) {
	/*
	 * v - начален връх
	 * u - краен връх
	 */

	return shortestPath(v, u).size() != 0;
}

bool TownMap::containsCycle(int v) {
	if (v <= 0 || v >= adjList.size()) {
		return false;
	}
	//обхождаме графа с DFS и ако срещнем някъв началния връх
	//значи съществува цикъл
	vector<bool> visited(adjList.size(), false);
	stack<int> s;
	visited[v] = true;
	vector<int> n = neighbours(v);
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

void TownMap::DFSEuler(int start, int v, set<pair<int, int> >& s,
		vector<int>& q) {
	if (s.empty() && start != v) {
		//q.pop_back();
		return;
	}
	vector<int> n = neighbours(v);
	for (int i = 0; i < n.size(); i++) {
		int u = n[i];
		pair<int, int> e = make_pair(v, u);
		if (s.find(e) != s.end()) {
			s.erase(e);
			DFSEuler(start, u, s, q);
			q.push_back(v);

		}

	}

}

vector<int> TownMap::eulerianCircuit() {
	set<pair<int, int> > edges;
	//пресмятаме броя на входящите и изходящите съседи
	vector<int> outgoing(adjList.size(), 0);
	vector<int> ingoing(adjList.size(), 0);
	for (int i = 0; i < adjList.size(); i++)
		for (int j = 0; j < adjList[i].size(); j++)
			if (adjList[i][j] > 0) {
				outgoing[i]++;
				ingoing[j]++;
				edges.insert(make_pair(i, j));
			}
	//ако броят им е различен,не съществува ойлеров цикъл
	for (int i = 1; i < adjList.size(); i++) {
		//cout << "ingoing: " << ingoing[i] << " outgoing: " << outgoing[i]<< endl;
		if (ingoing[i] != outgoing[i] || ingoing[i] == 0)
			return vector<int>();
	}
	vector<int> q(1, 1);
	DFSEuler(1, 1, edges, q);
	reverse(q.begin(), q.end());

	return q;

}

void TownMap::printTownMap() {
	for (int i = 1; i < adjList.size(); i++) {
		if (adjList[i].size() > 0) {
			cout << "Vertex: " << i << " - ";
			for (int j = 1; j < adjList[i].size(); j++)
				cout << adjList[i][j] << ' ';
			cout << endl;
		}
	}
}

vector<int> TownMap::alternativeRoutes(int v, int u, vector<int> unavailable) {
	/*
	 * v - връх от който тръгваме
	 * u - връх в който пристигаме
	 * unavailable - масив от върхове които са недостъпни
	 */
	vector<vector<int> > new_list;
	for (int i = 0; i < adjList.size(); i++) {
		if (!isIn(i, unavailable)) {
			new_list.push_back(adjList[i]);
		} else
			new_list.push_back(vector<int>(2, 0));
	}
	return TownMap(new_list).shortestPath(v, u);
	//return vector<int> ();
}

