#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <stack>
#include <iomanip>
using namespace std;

class Complex {
private:
   double real, imag;

public:
   Complex(double rl, double img): real(rl), imag(img) {};
   Complex(): real(0), imag(0){}
   Complex(int num):real(num), imag(0) {};

   const Complex& operator=(const Complex& rhs);
   void setReal(double num);
   void setImag(double num);
   double getReal() {return real;}
   double getImag() {return imag;}
   string toString() const;
   double norm() const;
   Complex reciprocal() const;

   class DivByZeroException {
   public:
      string toString() {return "Divide by zero exception";}
      string what() {return toString();}
   };

   // operators (the first one's signature is below for reference)
   friend Complex operator+(const Complex& a, const Complex& b);
   friend Complex operator+(const Complex& a, int num);
   friend Complex operator/(const Complex& a, const Complex& b);
   friend Complex operator*(const Complex& a, const Complex& b);
   friend Complex operator-(const Complex& a, const Complex& b);

   friend bool operator==(const Complex& a, const Complex& b);
   friend bool operator==(const Complex& a, const int num);
   friend bool operator<(const Complex& a, const Complex& b);
   friend ostream& operator<<(ostream& os, const Complex& a);



};
