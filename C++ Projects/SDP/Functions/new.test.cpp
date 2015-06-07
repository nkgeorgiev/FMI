/*
 * test.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: nikolay
 */

#include <string>
#include <vector>

using namespace std;

void q();
void foo(int a, int b);
void bar(int a, string c, vector<int> d);

void d() {
	d();
}

void c() {
}

void b() {
	b();
}

int a(string wtf) {
	foo();
	bar();
}

void bar(int a, string c, vector<int> d) {
	int e;
	for (int i = 0; i < 10; i++) {
		int b;
	}
	foo(e, b);
	a("sadad");
	q();
}

void foo(int a, int b) {
	string s;
	char c;
}

void q() {
	bar();
	foo();
}

