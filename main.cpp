#include <iostream>
#include "../JZlib/heads/jzlib.h"

#include <cstring>
// #include <cmath>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;
using JZlib::Bignum;



int main(int argc, char **argv, char **envp){
  Bignum a("298420000000411");
  Bignum b = "1000000";
  Bignum c(-22223123199);
  Bignum d("123456789101234567890");
  Bignum e("12300000000000000000000000000000000000000012390");
  Bignum x("-900000000");
  Bignum t;
  
  a.show();

  b.show();

  c.show();

  d.show();


  e.show();

  (d + e).show();

  t = d - e;
  t.show();

  (t + e).show();

  (d + c).show();

  (x * (x * -1)).show();

  (a * b).show();

  ((a * b) / b).show();

  return 0;
}


