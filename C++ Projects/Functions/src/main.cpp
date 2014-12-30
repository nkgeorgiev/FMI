#include <iostream>
#include <regex>
#include "FunctionOrder.h"
using namespace std;

void testFunction() {
	string func = "void foo(int a, int b){int b; cout<<a+b<<endl;";
	Function f(func);
	cout << f.getName() << endl;
	cout<<f.getDeclaration();
}

void testFunctionOrder() {
	FunctionOrder fo("test.cpp");
	fo.orderFunctions();
}

void testGraph() {

	Graph<int> a;
	a.add_edge(3, 8);
	a.add_edge(3, 10);
	a.add_edge(5, 11);
	a.add_edge(7, 8);
	a.add_edge(7, 11);
	a.add_edge(8, 9);
	a.add_edge(11, 2);
	a.add_edge(11, 9);
	a.add_edge(11, 10);


	a.print();
	cout << "-------------------\n";
	vector<int> sorted = a.topologicalSort();
	for (int i = 0; i < sorted.size(); i++)
		cout << sorted[i] << ' ';
	cout << endl;

	cout << "asbds";
}

int main() {
	testFunctionOrder();
	//testGraph();

	return 0;
}
