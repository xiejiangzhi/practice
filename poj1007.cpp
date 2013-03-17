#include <iostream>
#include <algorithm>

class DNA {
public:
  char *dna;
  short sum;

  DNA(const char *c, int len) {
    copy_dna(c, len);
    sum = dna_sum(dna);
  }

  ~DNA() {
    delete [] dna;
  }

  int dna_sum(const char * s) {
    int tmp = 0;

    for (int i = 0; s[i]; i++) {
      for (int j = i + 1; s[j]; j++) {
        if (s[i] > s[j]) { tmp += 1; }
      }
    }

    return tmp;
  }

  bool operator<(const DNA & d) const {
    return sum < d.sum;
  }

  void copy_dna(const char * c, int len) {
    dna = new char[len];

    for (int i = 0; i < len; i++) {
      dna[i] = c[i];
    }
  }
};

bool sort_by(const DNA * a, const DNA * b) {
  return *a < *b;
}


int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  int sum, len; char *cache;
  DNA **dnas;

  cin>>len>>sum; len += 1;

  cache = new char[len];
  dnas = new DNA*[sum];

  for (int i = 0; i < sum; i++) {
    cin>>cache;

    dnas[i] = new DNA(cache, len);
  }

  std::sort(dnas, dnas + sum, sort_by);

  for (int i = 0; i < sum; i++) {
    cout<<dnas[i]->dna<<endl;

    delete dnas[i];
  }

  delete [] dnas;

  return 0;
}
