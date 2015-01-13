#include <iostream>
#include <regex>
#include "FunctionOrder.h"
using namespace std;


int main() {
	FunctionOrder fo("test.cpp");
	fo.orderFunctions();
	return 0;
}

