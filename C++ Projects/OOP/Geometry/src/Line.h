/*
 * Line.h
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#ifndef LINE_H_
#define LINE_H_

#include "Vector.h"
#include "Point.h"

class Line {
	Point a;
	Vector v;

public:
	Line(const Point &, const Point &);
	Line(const Plane &, const Point &);
	Line(const Plane &, const Plane &);
	Line(const Point &, const Vector &);

	const Point& getA() const {
		return a;
	}

	void setA(const Point& a) {
		this->a = a;
	}

	const Vector& getV()const {
		return v;
	}

	void setV(const Vector& v) {
		this->v = v;
	}

	void printPEquation(ostream & = cout) const;
	void printPlanes(ostream & = cout) const;
	bool isColinear(const Line &) const;
	bool isSkew(const Line &)const;
	bool isColinear(const Plane &)const;
	bool isIn(const Plane &) const;
};

#endif /* LINE_H_ */
