/*
 * Point.h
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#ifndef POINT_H_
#define POINT_H_

class Line;
class Vector;
class Plane;


class Point {
	double a;
	double b;
	double c;

	Point operator-(const Point & p){
		return Point(a-p.a,b-p.b,c-p.c);
	}

	Point operator+(const Point & p){
		return Point(a+p.a,b+p.b,c+p.c);
	}

	Point operator*(double d){
		return Point(a*d,b*d,c*d);
	}


public:
	//конструктори
	Point();
	Point(double,double,double);
	Point(const Line &, const Line &);
	Point(const Line &, const Plane &);

	void translate(const Vector & v);

	double getA() const {
		return a;
	}

	void setA(double a) {
		this->a = a;
	}

	double getB() const {
		return b;
	}

	void setB(double b) {
		this->b = b;
	}

	double getC() const {
		return c;
	}

	void setC(double c) {
		this->c = c;
	}
	bool isOn(const Line &)const;
	bool isOn(const Plane &)const;

	friend ostream & operator<<(ostream & os,Point &p){
		return os<<p.a<<' '<<p.b<<' '<<p.c<<endl;
	}
};

#endif /* POINT_H_ */
