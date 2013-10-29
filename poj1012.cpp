#include <iostream>

using std::cout;

int eval(int k);
bool test_number(int k, int m);

#define MAX_K 14

int main() {
  int k;
  int cache[MAX_K];
  for (int i = 0; i < MAX_K; i++) { cache[i] = 0; }

  while (std::cin>>k) {
    if (k == 0) { break; }

    if (cache[k] == 0) { cache[k] = eval(k); }
    
    cout<<cache[k]<<"\n";
  }
}


int eval(int k) {
  int b = 0, m;

  while (b += 1) {
    m = b * (k + 1);
    if (test_number(k, m)) { return (m); }

    m = b * (k + 1) + 1;
    if (test_number(k, m)) { return (m); }
  }

  return -1;
}

bool test_number(int k, int m) {
  int p = 0, sum = k * 2;
  m -= 1;

  for (int i = 0; i < k; i++) {
    p += m; p %= sum--;
    if (p < k) { return false; }
  }

  return true;
}

