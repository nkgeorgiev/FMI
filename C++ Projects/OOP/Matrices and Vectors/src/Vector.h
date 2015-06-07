/*
 * Vector.h
 *
 *  Created on: May 17, 2014
 *      Author: nikolay
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
#include <iomanip>
using namespace std;

#include "Matrix.cpp"

template <typename T>
class Vector {
	T* arr;
	int size;

	void copy(const Vector &);
	void destroy();
public:
	//голяма четворка
	Vector();
	Vector(int);
	Vector(int,T*);
	Vector(const Vector &);
	~Vector();
	Vector& operator=(const Vector &);

	//събиране и изваждане на вектори
	void operator+=(const Vector &);
	Vector operator+(const Vector &);
	void operator-=(const Vector &);
	Vector operator-(const Vector &);

	//събиране, изваждане, умножение, и деление
	//на вектор с число
	void operator+=(const T &);
	Vector operator+(const T &);
	void operator-=(const T &);
	Vector operator-(const T &);
	void operator*=(const T &);
	Vector operator*(const T &);
	void operator/=(const T &);
	Vector operator/(const T &);

	//достъп до елемент на вектора
	T& operator[](int);

	//скаларно и векторно произведение
	double operator*(const Vector &);
	void operator^=(const Vector &);
	Vector operator^(const Vector &);

	//нормализиране на вектор
	void operator!();

	//умножение на вектор с матрица
	void operator*=(const Matrix<T> &);
	Vector operator*(const Matrix<T> &);


	//извеждане към изходен поток
	friend ostream& operator<<(ostream & os, const Vector<T> & v){
		for(int i=0;i<v.size;i++)
			os<<setprecision(3)<<v.arr[i]<<' ';
		os<<"\n";
		return os;
	}
	//въвеждане от входен поток
	friend istream& operator>>(istream & is, Vector<T> & v){
		is>>v.size;
		if(v.arr!=NULL)
			v.destroy();
		v.arr=new T[v.size];
		for(int i=0;i<v.size;i++)
			is>>v.arr[i];
		return is;
	}
};

#endif /* VECTOR_H_ */
