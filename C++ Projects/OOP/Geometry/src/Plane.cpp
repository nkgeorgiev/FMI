/*
 * Plane.cpp
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#include "headers.h"

Plane::Plane(): a(0), b(0), c(0), d(0) {}

Plane::Plane(double _a, double _b, double _c, double _d)
	:a(_a), b(_b), c(_c), d(_d) {}

Plane::Plane(const Plane & p, const Point & q){
	a=p.a;
	b=p.b;
	c=p.c;
	d=-a*q.getA()-b*q.getB()-c*q.getC();
}

Plane::Plane(const Line & l, const Point & p){
	if(p.isOn(l)){
		a=b=c=d=0;
		cout<<"The point is on the line!"<<endl;
	}
	else {
		/*
		 * Вземаме векторното произведение на 2та вектора
		 * образувани от 2 точки от правата и дадената точка
		 * Получения вектор е нормалния на равнината
		 */
		Point p1=l.getA();
		Vector v=l.getV();
		Point p2(p1.getA()+v.getX(),p1.getB()+v.getY(),p1.getC()+v.getZ());
		Vector v1(p1,p),v2(p2,p);
		Vector n=v1.crossProduct(v2);
		a=n.getX(),b=n.getY(),c=n.getZ();
		d=-1*(a*p.getA()+b*p.getB()+c*p.getC());
	}

}

Plane::Plane(const Vector & v, const Vector & u){
	Vector n=v.crossProduct(u);
	if(!n.isNull()){
		//същото като по-горе
		a=n.getX(),b=n.getY(),c=n.getZ();
		d=0;
	}
	else {
		a=b=c=d=0;
		cout<<"Vectors are colinear!!"<<endl;
	}
}

Plane::Plane(const Point & p1, const Point & p2, const Point & p3){
	Line l1(p1,p2);
	Vector v1(p1,p2);
	if(!p2.isOn(l1)){
		//същото като горе
		Vector v2(p2,p3);
		Vector n=v1.crossProduct(v2);
		a=n.getX(),b=n.getY(),c=n.getZ();
		d=-1*(a*p1.getA()+b*p1.getB()+c*p1.getC());
	}
	else {
		a=b=c=d=0;
		cout<<"The points are on the same line!!"<<endl;
	}
}

void Plane::printEquation(ostream & os) const {
	os<<a<<"*x + "<<b<<"*y + "<<c<<"*z + "<<d<<" = 0"<<endl;
}

void Plane::printPEquation(ostream & os) const {
	Point p1(0,0,-d);
	Point p2(1,1,-d-a-b);
	Vector v1(a,b,c);
	Vector v2(p1,p2);
	os<<"x = "<<p1.getA()<<" + "<<v1.getX()<<" * s"<<" + "<<v2.getX()<<" * t"<<endl;
	os<<"y = "<<p1.getB()<<" + "<<v1.getY()<<" * s"<<" + "<<v2.getX()<<" * t"<<endl;
	os<<"z = "<<p1.getC()<<" + "<<v1.getZ()<<" * s"<<" + "<<v2.getX()<<" * t"<<endl;

}

bool Plane::isColinear(const Plane &p) const{
	//ако коефициентите са пропорционални
	//равнините са колинеарни
	double  s1=a/p.getA(),
			s2=b/p.getB(),
			s3=c/p.getC();
	return abs(s1-s2)<eps && abs(s1-s3)<eps;

}

bool Plane::contains(const Line & l) const {
	return l.isIn(*this);
}
