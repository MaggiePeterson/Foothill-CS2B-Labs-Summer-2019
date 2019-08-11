// Test driver for the Complex number class
// &: Dec 2018

#include "Complex.h"

int main () {
   Complex a(1,2), b(3,4), c, e(1,1);

   c = a + b;
   cout << a << " + " << b << " = " << c << endl;

   c = a + 1;
   cout << a << " + " << 1 << " = " << c << endl;

  Complex d = 20;

   // TODO: Run more tests here

   try {
      c = a / b;
      cout << a << " / " << b << " = " << c << endl;
   } catch (Complex::DivByZeroException e) {
      cerr << e.what() <<endl;
   }

   // TODO: Run more tests here

   return 0;
}
