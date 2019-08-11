//
//  Complex.cpp
//  Lab5ComplexNumbers
//
//  Created by Margaret Peterson on 7/17/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#include "Complex.h"

const Complex& Complex::operator=(const Complex& rhs){
   this->real = rhs.real;
   this->imag = rhs.imag;
   return *this;
}


void Complex::setReal(double num){
   this->real = num;
}

void Complex::setImag(double num){
   this->imag = num;
}

string Complex::toString() const{

   std::ostringstream realOS;
    std::ostringstream imagOS;
   realOS << std::setprecision(8) << std::noshowpoint << real;
   imagOS << std::setprecision(8) << std::noshowpoint << imag;


   string output = "(" + realOS.str() + ", " + imagOS.str() + ")";
   return output;
}

double Complex::norm() const{

   return real*real + imag*imag;
}

Complex Complex::reciprocal() const{

   double normNum = norm();

   if(normNum < 1e-10)
      throw DivByZeroException();

   return Complex(real/normNum, -imag/normNum);
}

Complex operator+(const Complex& a, const Complex& b){

   return Complex(a.real + b.real, a.imag + b.imag);

}

Complex operator+(const Complex& a, int num){
   return Complex(a.real + num, a.imag);
}


Complex  operator/(const Complex& a, const Complex& b){
   Complex quot;
   quot = a * b.reciprocal();
   return quot;
}

Complex  operator*(const Complex& a, const Complex& b){
   //(a,b) * (c,d) = (ac-bd, ad+bc).
   return Complex(a.real*b.real - a.imag*b.imag, a.real*b.imag +  a.imag*b.real);
}

Complex  operator-(const Complex& a, const Complex& b){

   return Complex(a.real - b.real, a.imag - b.imag);
}

bool  operator==(const Complex& a, const Complex& b){

   return ((a.real == b.real) && (a.imag == b.imag));
}

bool  operator<(const Complex& a, const Complex& b){
   return (abs(a.norm()) < abs(b.norm()));
}

ostream& operator<<(ostream& os, const Complex& a){

   os<< std::setprecision(0)<< a.toString();
   return os;

}

bool operator==(const Complex& a, const int num){
   return (a.imag == num && a.real == num);
}




