//============================================================================
// Name        : prog2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

void prog2(){

	stack<bool> plates;
	queue<list<bool> > waiters;
	//input
	int a;
	cin>>a;
	while(a != -1){
		waiters.push(list<bool>());
		waiters.back().push_back(a);
		cin>>a;
		while(a != -1){
			waiters.back().push_back(a);
			cin>>a;
		}
		cin>>a;
	}
//	while(!waiters.empty()){
//		list<bool> waiter = waiters.front();
//		waiters.pop();
//		list<bool>::iterator it = waiter.begin();
//		while(it != waiter.end()){
//			cout<<*it<<' ';
//			it++;
//		}
//		cout<<endl;
//	}
	int k = 1, minute = 0;

	do{
		int numWashed = 0;
		int numBroken = 0;
		cout<<"***************"<<endl;
		cout<<minute<<" минута:"<<endl; minute++;
		bool popped = false;
		while(plates.size() < 15 && !waiters.empty()){
			cout<<"Келнер "<<k<<" оставя чинии"<<endl;
			k++;
			list<bool> waiter = waiters.front();
			waiters.pop(); popped = true;
			for(list<bool>::iterator it = waiter.begin(); it != waiter.end(); it++)
				plates.push(*it);
//			if(waiters.empty())
//				cout<<"Няма повече келнери"<<endl;

		}
		if(!popped)
			cout<<"Няма повече келнери"<<endl;
		while(numWashed < 7 && !plates.empty()){
			bool plate = plates.top(); plates.pop();
			if(plate)
				numWashed++;
			else
				numBroken++;
		}
		cout<<numWashed<<" измити чинии"<<endl;
		cout<<numBroken<<" счупени чинии"<<endl;


	} while(!plates.empty());



}

int main() {
	//prog2();
	stack<int> s;
	for(int i = 0; i< 10; i++)
		s.push(i);
	cout<<"adsad";
	return 0;
}
