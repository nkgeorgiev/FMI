/*
 * Vector.cpp
 *
 *  Created on: May 17, 2014
 *      Author: nikolay
 */

#include <stdexcept>

#include "Vector.h"

template<typename T>
void Vector<T>::copy(const Vector & v) {
	size = v.size;
	arr = new T[size];
	for (int i = 0; i < size; i++)
		arr[i] = v.arr[i];
}

template<typename T>
void Vector<T>::destroy() {
	delete[] arr;
}

template<typename T>
Vector<T>::Vector() {
	size = 0;
	arr = NULL;
}

template<typename T>
Vector<T>::Vector(int s):size(s){
	arr=new T[size];
	for(int i=0;i<size;i++)
		arr[i]=0;
}
template<typename T>
Vector<T>::Vector(int s, T* a) :
size(s) {
	arr = new T[size];
	for (int i = 0; i < size; i++)
		arr[i] = a[i];
}

template<typename T>
Vector<T>::Vector(const Vector & v) {
	copy(v);
}

template<typename T>
Vector<T>::~Vector() {
	destroy();
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> & v) {
	if (this != &v) {
		destroy();
		copy(v);
	}
	return *this;
}

template<typename T>
void Vector<T>::operator+=(const Vector<T> & v) {
	if (size != v.size) {
		cerr << "Wrong Dimensions";
		return;
	}
	for (int i = 0; i < size; i++)
		arr[i] += v.arr[i];
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector & v) {
	Vector tmp(*this);
	tmp += v;
	return tmp;
}

template<typename T>
void Vector<T>::operator-=(const Vector<T> & v) {
	if (size != v.size) {
		cerr << "Wrong Dimensions";
		return;
	}
	for (int i = 0; i < size; i++)
		arr[i] -= v.arr[i];
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector & v) {
	Vector tmp(*this);
	tmp -= v;
	return tmp;
}

template<typename T>
void Vector<T>::operator+=(const T & x) {
	for (int i = 0; i < size; i++)
		arr[i] += x;
}

template<typename T>
Vector<T> Vector<T>::operator+(const T & x) {
	Vector tmp(*this);
	tmp += x;
	return tmp;
}

template<typename T>
void Vector<T>::operator-=(const T & x) {
	for (int i = 0; i < size; i++)
		arr[i] -= x;
}

template<typename T>
Vector<T> Vector<T>::operator-(const T & x) {
	Vector tmp(*this);
	tmp -= x;
	return tmp;
}

template<typename T>
void Vector<T>::operator*=(const T & x) {
	for (int i = 0; i < size; i++)
		arr[i] *= x;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T & x) {
	Vector tmp(*this);
	tmp *= x;
	return tmp;
}

template<typename T>
void Vector<T>::operator/=(const T & x) {
	if (x == 0) {
		cerr << "Division by zero!!" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		arr[i] /= x;
}

template<typename T>
Vector<T> Vector<T>::operator/(const T & x) {
	Vector tmp(*this);
	tmp /= x;
	return tmp;
}

template<typename T>
T& Vector<T>::operator[](int i) {
	if (i >= 0 && i < size)
		return arr[i];
	//cerr<<"Out of Bounds!!"<<endl;
	//return arr[size - 1];
	throw out_of_range("Out of bounds");

}

template<typename T>
double Vector<T>::operator*(const Vector<T> & v) {
	double s = 0;
	for (int i = 0; i < size; i++)
		s += arr[i] * v.arr[i];
	return s;
}

template<typename T>
void Vector<T>::operator^=(const Vector<T> & v) {
	if (size != 3) {
		cerr << "Vector product is defined for 3D only!" << endl;
		return;
	}
	T a[3];
	a[0] = arr[1] * v.arr[2] - v.arr[1] * arr[2];
	a[1] = arr[2] * v.arr[0] - v.arr[2] * arr[0];
	a[2] = arr[0] * v.arr[1] - v.arr[0] * arr[1];
	arr[0] = a[0];
	arr[1] = a[1];
	arr[2] = a[2];
}

template<typename T>
Vector<T> Vector<T>::operator^(const Vector<T> & v) {
	Vector tmp(*this);
	tmp ^= v;
	return tmp;
}

template<typename T>
void Vector<T>::operator!() {
	double l = sqrt((*this) * (*this));
	for (int i = 0; i < size; i++)
		arr[i] /= l;
}

template<typename T>
void Vector<T>::operator*=(const Matrix<T> & m) {
	if (size != m.getRows()) {
		cerr << "Wrong dimensions!" << endl;
		return;
	}
	Vector tmp(*this);
	cout << tmp;
	for (int i = 0; i < m.getCols(); i++) {
		T s = 0;
		for (int j = 0; j < size; j++)
			s += tmp[j] * (m[j][i]);
		arr[i] = s;
	}
}

template<typename T>
Vector<T> Vector<T>::operator*(const Matrix<T> & m) {
	Vector tmp(*this);
	tmp *= m;
	return tmp;
}

