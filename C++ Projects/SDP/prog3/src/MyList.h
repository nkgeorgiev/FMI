/*
 * MyList.h
 *
 *  Created on: Jan 12, 2015
 *      Author: nikolay
 */

#ifndef MYLIST_H_
#define MYLIST_H_

#include "double_linked_list.cpp"
#include <climits>

class MyList: public DoubleLinkedList<int> {
private:
	MyList* joined;


public:
	void join(MyList& second);
	bool isJoined();
	int sum();
	int size();

};

#endif /* MYLIST_H_ */
