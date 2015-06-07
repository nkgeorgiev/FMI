/*
 * Matrix.cpp
 *
 *  Created on: May 11, 2014
 *      Author: nikolay
 */

#include <stdexcept>
#include "Matrix.h"

template <typename T>
void Matrix<T>::copy(const Matrix<T> & m){
	rows=m.rows;
	cols=m.cols;
	create(rows,cols);

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]=m.arr[i][j];
}


template <typename T>
void Matrix<T>::create(int a,int b){
	arr=new T*[a];
	for(int i=0;i<a;i++)
		arr[i]=new T[b];
}
template <typename T>
void Matrix<T>::destroy(){
	for(int i=0;i<rows;i++)
		delete[] arr[i];
	delete[] arr;
}

template <typename T>
int Matrix<T>::fgn(int k){
	int i=-1;
	T max=0;
	for(int j=0;j<cols;j++){
		if(abs(arr[k][j])>abs(max)){
			i=j;
			max=arr[k][j];
		}
	}
	return i;

}
template <typename T>
void Matrix<T>::swapRows(int k,int l){
	for(int i=0;i<cols;i++){
		swap(arr[k][i],arr[l][i]);
	}
}

template <typename T>
Matrix<T>::Matrix():arr(NULL),rows(0),cols(0){}

template <typename T>
Matrix<T>::Matrix(int r,int c):rows(r),cols(c){
	create(rows,cols);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & m){
	copy(m);
}

template <typename T>
Matrix<T>::~Matrix(){
	destroy();
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> & m){
	if(this != &m){
		destroy();
		copy(m);
	}
	return *this;
}

template <typename T>
void Matrix<T>::operator+=(const Matrix<T> & m){
	if(rows!=m.rows || cols!=m.cols){
		cerr<<"Wrong Dimensions!\n";
		return;
	}
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]+=m.arr[i][j];

}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & m){
	Matrix a(*this);
	a+=m;
	return a;
}

template <typename T>
void Matrix<T>::operator-=(const Matrix<T> & m){
	if(rows!=m.rows || cols!=m.cols){
		cerr<<"Wrong Dimensions!\n";
		return;
	}
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]-=m.arr[i][j];

}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & m){
	Matrix a(*this);
	a-=m;
	return a;
}

template <typename T>
void Matrix<T>::operator+=(const T & x){
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]+=x;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T & x){
	Matrix a(*this);
	a+=x;
	return a;
}

template <typename T>
void Matrix<T>::operator-=(const T & x){
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]-=x;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T & x){
	Matrix a(*this);
	a-=x;
	return a;
}

template <typename T>
T* Matrix<T>::operator[](int i) const{
	if(i>=0 && i<rows){
		return arr[i];
	}
	//cerr<<"Index out of bounds";
	throw out_of_range("Out of bounds");
}

template <typename T>
void Matrix<T>::operator*=(const Matrix<T> & m){
	if(cols!= m.rows){
		cerr<<"Wrong dimensions!";
		return;
	}
	//правим копие на матрицата
	Matrix tmp(*this);
	//умножаваме копието с m и записваме в оригиналната
	for(int i=0;i<rows;i++){
		for(int j=0;j<m.cols;j++){
			T sum=0;
			for(int k=0;k<cols;k++)
				sum+=tmp.arr[i][k]*m.arr[k][j];
			arr[i][j]=sum;
		}
	}

}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & m){
	Matrix tmp(*this);
	tmp*=m;
	return tmp;
}

template <typename T>
void Matrix<T>::operator*=(const T & x){
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]*=x;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(const T & x){
	Matrix tmp(*this);
	tmp*=x;
	return tmp;
}

template <typename T>
void Matrix<T>::operator/=(const T & x){
	if(x==0){
		cerr<<"Division by zero!";
		return;
	}
	for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				arr[i][j]/=x;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T & x){
	Matrix tmp(*this);
	tmp/=x;
	return tmp;
}

template <typename T>
void Matrix<T>::operator~(){
	//копираме матрицата
	Matrix tmp(*this);
	//трием матрицата и създаваме нова с разменени размерности
	destroy();
	rows=tmp.cols;
	cols=tmp.rows;
	create(rows,cols);
	//пренасяме елементите от копието на старата в новата
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]=tmp.arr[j][i];

}

template <typename T>
double Matrix<T>::getDeterminant() const{
	Matrix tmp(*this);
	if(rows!=cols){
		cerr<<"Determinant is defined for square matrices only"<<endl;
		return 0;
	}
	double det=1;
	double eps=1e-6;
	for(int k=0;k<rows-1;k++){
	   //намираме най-големият елемент в колона к
	   int index=tmp.fgn(k);
	   //ако всички елементи в колоната са 0
	   //детерминантата е 0
	   if(index==-2){
		   return 0;
	   }
	   //разменяме к-ти ред с ред index
	   if(k!=index){
		   tmp.swapRows(k,index);
		   det*=-1;
	   }
	   //по метода на Гаус нулираме всичко под к-ти ред
	   for(int i=k+1;i<rows;i++){
		   for(int j=k+1;j<cols;j++){
			   tmp.arr[i][j]=tmp.arr[i][j]-tmp.arr[k][j]*(tmp.arr[i][k]/tmp.arr[k][k]);
			   if(abs(tmp.arr[i][j])<eps) tmp.arr[i][j]=0;
		   }
		   tmp.arr[i][k]=0;
	   }
	}
	//в получената горно-диагонална матрица
	//детерминантата е произведението на всички елементи
	//по главния диагонал
	for(int i=0;i<rows;i++){
		det*=tmp.arr[i][i];
	}
	return det;
}

template <typename T>
void Matrix<T>::gauss(){
    double eps=1e-6;
    //int a=1;
    for(int k=0;k<rows-1;k++){
    	//намираме най-големият елемент в колона к
        int index=fgn(k);
        //ако цялата колона е от нули минаваме на следващата колона
        if(index==-1){
        	//swapRows(index,rows-a);
        	continue;
        }
        //разменяме к-ти ред с ред index
        if(k!=index){
            swapRows(k,index);
        }
        //нулираме всички елементи от колона k
        //под ред k
        for(int i=k+1;i<rows;i++){
            for(int j=k+1;j<cols;j++){
            	if(arr[k][k]!=0)
            		arr[i][j]=arr[i][j]-arr[k][j]*(arr[i][k]/arr[k][k]);
                if(abs(arr[i][j])<eps)
                    arr[i][j]=0;
            }
            arr[i][k]=0;
        }
    }
}


template <typename T>
void Matrix<T>::diagonalize(){
	//правим горно-диагонална матрица
	gauss();
    double eps=1e-6;
    //нулираме елементите над  k-ти ред
    for(int k=rows-1;k>0;k--){
        for(int i=0;i<k;i++){
            for(int j=0;j<cols;j++){
                if(j!=k && arr[k][k]){
                    arr[i][j]=arr[i][j]-arr[k][j]*(arr[i][k]/arr[k][k]);

                    if(abs(arr[i][j])<eps) arr[i][j]=0;
                }
            }
            arr[i][k]=0;
        }
    }



}

template <typename T>
Matrix<T> Matrix<T>::operator!(){
	//ако детерминантата е 0 няма обратна матрица
	if(!getDeterminant()){
		cerr<<"Inverse matrix doesn't exist!";
		return *this;
	}
	//правим нова матрица с размер rows x 2*cols
	//и като залепяме единичната към оригиналната матрица
	Matrix tmp(rows,2*cols);
	for(int i=0;i<rows;i++){
		tmp.arr[i][i+cols]=1;
		for(int j=0;j<cols;j++)
			tmp.arr[i][j]=arr[i][j];
	}
	//диагонализираме tmp
	tmp.diagonalize();
	//превръщаме оригиналната матрица в единична
	double eps=1e-6;
		for(int i=0;i<rows;i++){
			double x=tmp.arr[i][i];
			for(int j=0;j<2*cols;j++){
				tmp.arr[i][j]=tmp.arr[i][j]/x;
				if(abs(tmp.arr[i][j])<eps)
					tmp.arr[i][j]=0;
			}
		}
	//обратната матрица се получава на
	//мястото на единичната
	Matrix inverse(rows,cols);
	//копираме обратната матрица в inverse
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			inverse.arr[i][j]=tmp.arr[i][j+cols];
	return inverse;
}
