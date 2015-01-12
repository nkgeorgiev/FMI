/*
 * MyList.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: nikolay
 */

#include "MyList.h"

void MyList::join(MyList& second) {
	if (isJoined() || second.isJoined())
		return;
	DoubleListElement<int> *firstList = this->front;
	DoubleListElement<int> *secondList = second.back;
	DoubleListElement<int> * first_tmp;
	DoubleListElement<int> * second_tmp;

	int max = INT_MIN, idx1 = 0, idx2 = 0;
	int f_size = this->size(), s_size = second.size();
	while (firstList != NULL) {
		secondList = second.back;
		idx2 = 0;
		while (secondList != NULL) {
			if (firstList->data == secondList->data
					&& (idx1 == idx2 || f_size - idx1 == s_size - idx2)) {
				if (firstList->data > max) {
					first_tmp = firstList;
					second_tmp = secondList;
					max = firstList->data;
				}
			}
			secondList = secondList->prev;
			idx2++;
		}
		firstList = firstList->next;
		idx1++;
	}
	if (first_tmp != NULL && second_tmp != NULL) {
		this->back->next = second_tmp;
		while(this->back->next != NULL)
			this->back = this->back->next;

		second.front->prev = first_tmp;
		while(second.front->prev != NULL)
			second.front = second.front->prev;
		joined = &second;
		second.joined = this;
		cout << "Joined at:" << max << endl;

	}
	//second.join(*this);

}


bool MyList::isJoined() {
	DoubleListElement<int> *dle = this->front;
	while (dle->next != NULL) {
		if (dle->next->prev != dle) {
			return true;

		}
		dle = dle->next;
	}
	return false;

}

int MyList::sum() {
	int f_sum = 0, b_sum = 0;
	DoubleListElement<int> *dle = this->front;
	if (isJoined()) {
		while (dle != NULL && dle == dle->next->prev) {
			f_sum += dle->data;
			dle = dle->next;
		}
		if (dle != NULL)
			f_sum += dle->data;
		dle = this->back;
		while (dle != NULL && dle == dle->prev->next) {
			b_sum += dle->data;
			dle = dle->prev;
		}
		if (dle != NULL)
			b_sum += dle->data;
		return f_sum + b_sum;
	}
	while (dle != NULL) {
		f_sum += dle->data;
		dle = dle->next;
	}
	return f_sum;
}

int MyList::size() {
	int size = 0;
	DoubleListElement<int> *dle = this->front;
	while (dle != NULL) {
		size++;
		dle = dle->next;
	}
	return size;
}
