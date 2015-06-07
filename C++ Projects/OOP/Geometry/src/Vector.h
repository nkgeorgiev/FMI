/*
 * Vector.h
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "headers.h"
class Point;
class Line;
class Plane;

class Vector {
	double x;
	double y;
	double z;

public:
	//конструктори
	Vector();
	Vector(double,double,double);
	Vector(const Point &, const Point &);
	Vector(const Plane &);

	void operator+=(const Vector &);
	Vector operator+(const Vector &);
	double scalarProduct(const Vector &) const ;
	Vector crossProduct(const Vector &)const;

	operator Point(){
		return Point(x,y,z);
	}

	bool isNull(){
		return x==0 && y==0 && z==0;
	}

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	int getZ() const {
		return z;
	}

	void setZ(int z) {
		this->z = z;
	}

	friend ostream& operator<<(ostream & os, const Vector &v){
		return os<<v.x<<' '<<v.y<<" "<<v.z<<endl;
	}
};

#endif /* VECTOR_H_ */
