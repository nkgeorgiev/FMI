//============================================================================
// Name        : Geometry.cpp
// Author      : Nikolay
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "headers.h"

void testPoint(){
	Point a,b(1,1,1),c(2,3,1);
	//cout<<a<<b<<c<<endl;
	Line l1(a,Point(0,1,0)),l2(b,Point(0,1,0));
	Point p1(l1,l2);
	cout<<p1; //0 1 0
	Plane pl1(1,0,0,0);
	Point p2(l2,pl1);
	cout<<p2; //0 1 0
	p2.translate(Vector(2,3,4));
	cout<<p2; //2 4 4
	cout<<a.isOn(l1)<<endl;//true
	cout<<b.isOn(pl1)<<endl; //false
}

void testVector(){
	Point p1(1,0,0),p2(2,1,1);
	Plane pl1(1,0,0,0);
	Vector v1,v2(p1,p2),v3(pl1);
	cout<<v1<<v2<<v3;
	v1+=v3;
	cout<<v1;
	v1=v1+v2;
	cout<<v1;
	cout<<v1.scalarProduct(v2)<<endl;
	cout<<v1;
	cout<<v1.crossProduct(v3);

}

void testLine(){
	Point p1,p2(1,1,1),p3(2,3,1);
	Plane pl1(1,0,0,0),pl2(0,1,3,1);
	cout<<"alive"<<endl;
	Line l1(p1,Point(0,1,0)),l2(pl1,p2);
	Line l3(pl1,pl2),l4(p3,Vector(2,1,3));
	l1.printPEquation();
	cout<<endl;
	l2.printPEquation();
	cout<<endl;
	l3.printPEquation();
	cout<<endl;
	l4.printPEquation();
	cout<<endl;
	Line(Point(2,3,1),Vector(2,2,4)).printPlanes();
}

void testPlane(){
	Point p1,p2(1,1,1),p3(2,3,1);
	Line l1(p1,Point(0,1,0)),l2(p2,Point(0,1,0));
	Plane pl1;
	Vector v1,v2(p1,p2),v3(pl1);
	Plane pl2(Plane(2,3,3,1),p1);
	Plane pl3(l1,p3),pl4(v2,Vector(2,2,1)),pl5(4,2,1,0);
	pl1.printEquation();
	pl2.printEquation();
	pl3.printEquation();
	pl4.printEquation();
	pl5.printEquation();
	cout<<endl;
	pl5.printPEquation();
	cout<<pl1.isColinear(pl3)<<endl;
	cout<<pl3.contains(l1);
}

int main() {
	//testPoint();
	//testVector();
	testLine();
	//testPlane();


	return 0;
}
