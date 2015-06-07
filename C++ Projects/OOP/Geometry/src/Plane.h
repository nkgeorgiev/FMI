/*
 * Plane.h
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#ifndef PLANE_H_
#define PLANE_H_

class Point;
class Line;
class Vector;

class Plane {
	double a;
	double b;
	double c;
	double d;

public:
	Plane();
	Plane(double,double,double,double);
	Plane(const Plane &, const Point &);
	Plane(const Line &, const Point &);
	Plane(const Vector &, const Vector &);
	Plane(const Point &, const Point &, const Point&);

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

	double getD() const {
		return d;
	}

	void setD(double d) {
		this->d = d;
	}

	void printEquation(ostream & =cout) const;
	void printPEquation(ostream & =cout) const;
	bool isColinear(const Plane &)const;
	bool contains(const Line &) const;
};

#endif /* PLANE_H_ */
