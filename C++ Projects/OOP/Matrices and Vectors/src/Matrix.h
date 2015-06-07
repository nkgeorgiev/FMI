/*
 * Matrix.h
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;



template <typename T>
class Matrix {
	T** arr;
	int rows;
	int cols;

	void copy(const Matrix &); //копира матрицата
	void create(int,int);//заделя памет за матрицата
	void destroy(); //изтрива матрицата
	void swapRows(int, int); //разменя 2 реда
	int fgn(int); //намира най-голямото число
				  //по модул в колона к
	void gauss();//метод на Гаус за горно-диагонална матрица

//конструктори
public:
	//голяма четворка
	Matrix();
	Matrix(int,int);
	Matrix(const Matrix &);
	~Matrix();
	Matrix& operator=(const Matrix &);

	//селектори
	int getRows()const { return rows;}
	int getCols()const {return cols;}


	//прибавяне или изваждане на матрица
	//ако 2те са с еднакви размерности
	void operator+=(const Matrix &);
	Matrix operator+(const Matrix &);
	void operator-=(const Matrix &);
	Matrix operator-(const Matrix &);

	//прибавяне или изваждане на число от
	//всеки елемент на матрицата
	void operator+=(const T &);
	Matrix operator+(const T &);
	void operator-=(const T &);
	Matrix operator-(const T &);

	//умножение на матрицa с матрица
	void operator*=(const Matrix &);
	Matrix operator*(const Matrix &);

	//умножение и деление на матрици с числа
	void operator*=(const T &);
	Matrix operator*(const T &);
	void operator/=(const T &);
	Matrix operator/(const T &);

	//достъп до елемент
	T* operator[](int) const ;

	//транспониране
	void operator~();

	void diagonalize();//диагонализиране на матрица

	//намиране на детерминанта
	double getDeterminant() const;

	//намиране на обратна матрица
	Matrix operator!();

	//извеждане към изходен поток
	friend ostream& operator<<(ostream & os, const Matrix<T> & m){
		if(m.arr != NULL){
			for(int i=0;i<m.rows;i++){
				for(int j=0;j<m.cols;j++)
					os<<setw(5)<<setprecision(3)<<m.arr[i][j]<<' ';
				os<<endl;
			}
		}
		return os;
	}
	//въвеждане от входен поток
	friend istream& operator>>(istream & is, Matrix<T> & m){
		if(m.arr != NULL)
			m.destroy();
		is>>m.rows>>m.cols;

		m.create(m.rows,m.cols);

		for(int i=0;i<m.rows;i++)
			for(int j=0;j<m.cols;j++)
				is>>m.arr[i][j];
		return is;
	}

};

#endif /* MATRIX_H_ */
