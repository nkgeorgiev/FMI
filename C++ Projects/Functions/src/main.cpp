#include <iostream>
#include <regex>
#include "FunctionOrder.h"
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
	string func = "void foo(int a, int b){int b; cout<<a+b<<endl;";
	vector<string> s = multi_split(func, "{;}");
	for(int i = 0; i < s.size(); i++){
		cout<<s[i]<<endl;
	}
	return 0;
}
