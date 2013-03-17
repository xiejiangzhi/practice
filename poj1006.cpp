#include <iostream>

#define MAX_DAY   (23 * 28 * 33)
#define PTIMES    23
#define ETIMES    28
#define ITIMES    33

short next_day(short p, short e, short i, short d) {
  p %= PTIMES; e %= ETIMES; i %= ITIMES;

  while (true) {
    if (p <= e && p < i || p < e && p <= i) { p += PTIMES; }
    else if (e <= p && e < i || e < p && e <= i) { e += ETIMES; }
    else if (i <= p && i < e || i < p && i <= e) { i += ITIMES; }

    if (p == e && p == i) {
      if (p <= d) {
        return MAX_DAY + p - d;
      } else {
        return p - d;  
      }
    }
  }
}

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  short p, e, i, d;
  int sum = 0;

  while (++sum) {
    cin>>p>>e>>i>>d;

    if (p == -1 && e == -1 && i == -1 && d == -1) { break; }

    cout<<"Case "<<sum<<": the next triple peak occurs in "
        <<next_day(p, e, i, d)<<" days."<<endl;
  }


  return 0;
}
