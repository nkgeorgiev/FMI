/*
 * Point.cpp
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#include "headers.h"

//double eps = 1e-6;
Point::Point():a(0.0), b(0.0), c(0.0){}

Point::Point(double _a, double _b, double _c)
	:a(_a), b(_b), c(_c){}

Point::Point(const Line & l1, const Line & l2){
	//ако правите са колинеарни или кръстосани
	if(l1.isColinear(l2) || l1.isSkew(l2)){
		a=0,b=0,c=0;
	}
	else {
		//Волфрама така казва
		Point tmp;
		Point a1=l1.getA(),a2=l2.getA();
		Vector v1=l1.getV(),v2=l2.getV();
		Vector v3=v1.crossProduct(v2);
		Vector v4=Vector(a1,a2).crossProduct(v2);
		Point t=(Point)v1;
		tmp=a1+ t*((v3.scalarProduct(v4)/v3.scalarProduct(v3)));
		a=tmp.a; b=tmp.b; c=tmp.c;
	}
}

Point::Point(const Line & l, const Plane & p){
	double a1=l.getA().getA(),a2=l.getA().getB(),
			a3=l.getA().getC();
	double v1=l.getV().getX(),v2=l.getV().getY(),
			v3=l.getV().getZ();
	//заместваме уравненията на правата в уравнението на
	//равнината и гледаме коефициента пред параметъра
	double f=p.getA()*a1+p.getB()*a2+p.getC()*a3+p.getD();
	double g=p.getA()*v1+p.getB()*v2+p.getC()*v3;
	if(abs(g)<eps){
		a=0,b=0,c=0;
	}
	else {
		double s=-f/g;
		a=a1+s*v1;
		b=a2+s*v2;
		c=a3+s*v3;
	}
}

void Point::translate(const Vector & v){
	a+=v.getX();
	b+=v.getY();
	c+=v.getZ();
}

bool Point::isOn(const Line & l) const {
	//гледаме дали в уравненията на правата параметърът е еднакъв за всяка координата
	double u=a- l.getA().getA();
	double v=b- l.getA().getB();
	double w=c- l.getA().getC();
	u = (l.getV().getX()!= 0 ? u/l.getV().getX() : u);
	v = (l.getV().getY()!= 0 ? v/l.getV().getY() : v);
	w = (l.getV().getZ()!= 0 ? w/l.getV().getZ() : w);

	return abs(u-v)<eps && abs(u-w)<eps;
}

bool Point::isOn(const Plane & p)const {
	return abs(p.getA()*a + p.getB()*b + p.getC()*c + p.getD())<eps;
}
