/*
 * Vector.cpp
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#include "headers.h"

Vector::Vector():x(0),y(0),z(0) {}

Vector::Vector(double _x,double _y, double _z)
	:x(_x),y(_y),z(_z) {}

Vector::Vector(const Point & p1, const Point & p2){
	x=p2.getA()-p1.getA();
	y=p2.getB()-p1.getB();
	z=p2.getC()-p1.getC();
}

Vector::Vector(const Plane & p){
	x=p.getA();
	y=p.getB();
	z=p.getC();
}

void Vector::operator +=(const Vector & v){
	x+=v.x;
	y+=v.y;
	z+=v.z;

}

Vector Vector::operator+(const Vector & v){
	Vector tmp(*this);
	tmp+=v;
	return tmp;
}

double Vector::scalarProduct(const Vector & v) const {
	double res = x*v.x + y*v.y + z*v.z;
	return (abs(res)<eps ? 0 : res);
}

Vector Vector::crossProduct(const Vector & v) const{
	double a=y*v.z - v.y*z;
	double b=z*v.x - x*v.z;
	double c=x*v.y - y*v.x;
	return Vector(a,b,c);
}
