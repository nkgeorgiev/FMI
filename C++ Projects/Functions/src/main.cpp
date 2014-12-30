#include <iostream>
#include <regex>
#include "FunctionOrder.h"
#include "Graph.cpp"
using namespace std;




void testFunction() {
	string func = "void foo(int a, int b){int b; cout<<a+b<<endl;";
	Function f(func);
	cout << f.getName() << endl;
	cout << f.getRetType() << endl;
	;
	vector<string> a = f.getArgs();
	vector<string> b = f.getArgsType();
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << ' ' << b[i] << endl;
	}
}

void testFunctionOrder(){
	FunctionOrder fo("test.cpp");
}

int main() {
	//testFunctionOrder();
	Graph<int> a;
	a.add_Edge(3,4);
	a.add_Edge(10,4);
	a.add_Edge(10,3);
	//a.remove_edge(10,3);
	a.add_Edge(4, 3);
	a.add_Edge(4,10);
//	a.remove_edge(3,4);
//	a.remove_edge(10,4);
	a.print();
//	//a.remove_cycles();
	cout<<"-------------------\n";
	a.print();
	vector<int> sorted = a.topologicalSort();
	for(int i = 0; i< sorted.size(); i++)
		cout<<sorted[i]<<' ';
	cout<<endl;

	cout<<"asbds";
	return 0;
}
