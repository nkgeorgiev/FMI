/*
 * Line.cpp
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#include "headers.h"
#include "Matrix.cpp"


double eps= 1e-6;

Line::Line(const Point & p, const Point & q){
	a=p;
	v=Vector(p,q);
}

Line::Line(const Plane & p, const Point & q){
	a=q;
	v=Vector(p);
}

Line::Line(const Plane & p, const Plane & q){

	/*
	 * намираме векторното произведение на нормалните вектори
	 * и вземаме точка която принадлежи и на 2те равнини
	 */
	if(p.isColinear(q)){
		v=Vector(0,0,0);
		a=Point(0,0,0);

	} else{
		double a1=p.getA(),b1=p.getB(),c1=p.getC(),d1=p.getD();
		double a2=q.getA(),b2=q.getB(),c2=q.getC(),d2=q.getD();
		Vector v1(p.getA(),p.getB(),p.getC());
		Vector v2(q.getA(),q.getB(),q.getC());
		v=v1.crossProduct(v2);

		//точката вземаме като решение на система
		Matrix<double> m(3,4);
		m[0][0]=a1,m[0][1]=b1,m[0][2]=c1,m[0][3]=-d1;
		m[1][0]=a2,m[1][1]=b2,m[1][2]=c2,m[1][3]=-d2;
		m[2][0]=v.getX(),m[2][1]=v.getY(),m[2][2]=v.getZ(),m[2][3]=0;

		//cout<<m;
		m.diagonalize();
		//cout<<m;
		m[0][0]==0 ? a.setA(0) : a.setA(m[0][3]/m[0][0]);
		m[1][1]==0 ? a.setB(0) : a.setB(m[1][3]/m[1][1]);
		m[2][2]==0 ? a.setC(0) : a.setC(m[2][3]/m[2][2]);


	}

}

Line::Line(const Point & p,const Vector & q){
	a=p;
	v=q;
}

void Line::printPEquation(ostream & os)const{
	os<<"x = "<<a.getA()<<" + "<<v.getX()<<" * s"<<endl;
	os<<"y = "<<a.getB()<<" + "<<v.getY()<<" * s"<<endl;
	os<<"z = "<<a.getC()<<" + "<<v.getZ()<<" * s"<<endl;

}

void Line::printPlanes(ostream& os) const {
	/*
	 *ако правата е в 1 от координатните равнини
	 *вземаме  точка от перпендикулярната координатна ос
	 *и правим равнина през правата и тази точка
	 */
	if(isIn(Plane(1,0,0,0))){
		Plane(1,0,0,0).printEquation(os);
		Plane(*this,Point(1,0,0)).printEquation(os);
		return;
	}
	if(isIn(Plane(0,1,0,0))){
			Plane(0,1,0,0).printEquation(os);
			Plane(*this,Point(0,1,0)).printEquation(os);
			return;
		}
	if(isIn(Plane(0,0,1,0))){
			Plane(0,0,1,0).printEquation(os);
			Plane(*this,Point(0,0,1)).printEquation(os);
			return;
		}
	/*
	 *ако не, вземаме координатна ос която е кръстосана
	 *на правата и правим 2 равнини през различни точки
	 *от тази координатна ос
	 */
	Line l1(Point(1,0,0),Point(0,0,0));
	Line l2(Point(0,1,0),Point(0,0,0));
	Line l3(Point(0,0,1),Point(0,0,0));
	if(isSkew(l1)){
		Plane(*this,Point(1,0,0)).printEquation(os);
		Plane(*this,Point(0,0,0)).printEquation(os);
		return;
	}
	if(isSkew(l2)){
		Plane(*this,Point(0,1,0)).printEquation(os);
		Plane(*this,Point(0,0,0)).printEquation(os);
		return;
	}
	if(isSkew(l3)){
		Plane(*this,Point(0,0,1)).printEquation(os);
		Plane(*this,Point(0,0,0)).printEquation(os);
		return;
	}

}

bool Line::isColinear(const Line & l) const {
	//2 прави са успоредни ако векторното им произведение е 0
	Vector tmp = v.crossProduct(l.getV());
	return abs(tmp.getX())<eps && abs(tmp.getY())<eps
			&& abs(tmp.getZ())<eps;
}

bool Line::isSkew(const Line & l) const {
	//така каза волфрам
	Vector v1(l.a,a);
	Vector v2=v.crossProduct(l.v);
	return !abs(v1.scalarProduct(v2))<eps;

}

bool Line::isColinear(const Plane & p) const {
	//пак от волфрам
	double v1=getV().getX(),v2=getV().getY(),
			v3=getV().getZ();
	double g=p.getA()*v1+p.getB()*v2+p.getC()*v3;
	if(abs(g)<eps){
		return true;
	}
	else {
		return false;
	}
}

bool Line::isIn(const Plane & p)const {
	if(a.isOn(p) && isColinear(p))
		return true;
	return false;

}
