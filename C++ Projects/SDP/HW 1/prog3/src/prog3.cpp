#include <iostream>
#include "MyList.h"
using namespace std;

int main() {
	MyList l1;
	MyList l2;
	MyList l3;

	l1.insertEnd(1);
	l1.insertEnd(2);
	l1.insertEnd(3);
	l1.insertEnd(4);
	l1.insertEnd(5);
	l1.insertEnd(6);

	l2.insertEnd(0);
	l2.insertEnd(1);
	l2.insertEnd(2);
	l2.insertEnd(3);
	l2.insertEnd(4);

	cout << "l1: " << l1;
	cout << "l2: " << l2;
	cout << "l1 isJoined: " << l1.isJoined() << endl;
	cout << "l2 isJoined: " << l2.isJoined() << endl;

	l1.join(l2);

	cout << "l1 isJoined: " << l1.isJoined() << endl;
	cout << "l2 isJoined: " << l2.isJoined() << endl;

	cout << "The sum of l1 is: " << l1.sum() << endl;
	cout << "The sum of l2 is: " << l2.sum() << endl;


	return 0;
}
