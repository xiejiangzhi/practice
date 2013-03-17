#include <iostream>

inline int sum(double len) {
  double tmp = 0;

  for (int i = 2; ; i++) {
    tmp += 1.0 / i;

    if (tmp >= len) { return i - 1; }
  }
}


int main() {
  using std::cout;
  using std::endl;
  using std::cin;

  double len;

  while (cin>>len) {
    if (len == 0) { break; }

    cout<<sum(len)<<" card(s)"<<endl;
  }

  return 0;
}
