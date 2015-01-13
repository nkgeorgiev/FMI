#ifndef MYLIST_H_
#define MYLIST_H_

#include "double_linked_list.cpp"
#include <climits>

class MyList: public DoubleLinkedList<int> {
public:
	void join(MyList& second);
	bool isJoined();
	int sum();
	int size();

};

#endif /* MYLIST_H_ */
