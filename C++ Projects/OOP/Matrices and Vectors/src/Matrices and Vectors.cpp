/*
 * Matrices and Vectors.cpp
 *
 *  Created on: May 11,2014
 *  	Author: nikolay
 */

#include <iostream>
#include <cstdio>
using namespace std;


#include "Vector.cpp"

void testMatrix(){
	freopen("input.txt","r",stdin);
		Matrix<double> a(3,3),b;

		cin>>a>>b;
		Matrix<double> c=a,d(b);
		cout<<"Mатрица А\n"<<a<<"\nМатрица B\n"<<b<<endl;

		cout<<"Mатрица C\n"<<c<<"\nМатрица D\n"<<d<<endl;
		cout<<"Детерминантата на С е: "<<c.getDeterminant()<<endl;
		cout<<"Обратна матрица на A:\n"<<!a<<endl;

		cout<<"A + B:\n"<<a+b<<endl;
		cout<<"A - B:\n"<<a-b<<endl;
		cout<<"A + 5:\n"<<a+5<<endl;
		cout<<"B - 2:\n"<<b-2<<endl;
		cout<<"A * C:\n"<<a*c<<endl;
		cout<<"B * 4:\n"<<b*4<<endl;
		cout<<"C / 3:\n"<<c/3<<endl;
		cout<<a[2][1]<<endl;
		~d;
		cout<<"Транспонираната на D:\n"<<d<<endl;
		c.diagonalize();
		cout<<"Диагонализиране на C:"<<endl;
		cout<<c<<endl;
}

void testVector(){

	freopen("inputV.txt","r",stdin);
	Matrix<double> m;
		cin>>m;
	Vector<double> a,b;
	cin>>a>>b;
	cout<<"Вектор a:\n"<<a<<"Вектор b:\n"<<b<<endl;
	cout<<"a[0]: "<<a[0]<<endl;
	cout<<"Скаларно произведение на a & b : "<<a*b<<endl;
	Vector<double> c=a^b;
	cout<<"Векторно произведение на a & b: "<<c<<endl;
	!b;
	cout<<"Нормализиране на b: "<<b;
	cout<<"Вектор a * Матрица m: "<<a*m;
	cout<<"a + b: "<<a+b;
	cout<<"a - b: "<<a-b;
	cout<<"a + 3: "<<a+3;
	cout<<"b - 2: "<<b-2;
	cout<<"a * 0.5: "<<a*0.5;
	cout<<"b / 10: "<<b/10;
}
int main() {
	cout<<"Testing Matrix:"<<endl;
	cout<<"---------------------------"<<endl;
	testMatrix();
	cout<<"---------------------------"<<endl;
	cout<<"\nTesting Vector:"<<endl;
	cout<<"---------------------------"<<endl;
	testVector();
	cout<<"---------------------------"<<endl;

	return 0;
}
