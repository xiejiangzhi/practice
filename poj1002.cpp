#include <iostream>
#include <cstdlib>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;

#define STRLEN      128
#define PHONE       (7 + 1)

inline char abc_to_i(char c) {
  switch (c) {
  case 'A': ; case 'B': ; case 'C':
    return '2';
  case 'D': ; case 'E': ; case 'F':
    return '3';
  case 'G': ; case 'H': ; case 'I':
    return '4';
  case 'J': ; case 'K': ; case 'L':
    return '5';
  case 'M': ; case 'N': ; case 'O':
    return '6';
  case 'P': ; case 'R': ; case 'S':
    return '7';
  case 'T': ; case 'U': ; case 'V':
    return '8';
  case 'W': ; case 'X': ; case 'Y':
    return '9';
  default:
    return c;
  }
}

int str_to_phone(char *cache) {
  char c, out_phone[PHONE] = {0};

  for (int i = 0, j = 0; i < STRLEN && cache[i] != 0; i++) {
    c = cache[i];

    if (c == '-') { continue; }

    if (c > '9') {
      c = abc_to_i(c);
    }

    out_phone[j++] = c;
  }

  return atoi(out_phone);;
}

void sort_phones(int *phones, int sum) {
  std::sort(phones, phones + sum);
}

void out(int *phones, int sum) {
  int i, j, k = 0;

  for (i = 0; i < sum; i++) {
    for (j = i + 1; j < sum; j++) {
      if (phones[j] != phones[i]) { break; }
    }

    if (j - i > 1) {
      cout.width(3);
      cout.fill('0');
      cout.setf(std::ios::right);
      cout<<(phones[i] / 10000)<<"-";

      cout.width(4);
      cout.fill('0');
      cout.setf(std::ios::right);
      cout<<(phones[i] % 10000)<<" ";

      cout<<(j - i)<<endl;
      k++;
    }

    i = j - 1;
  }
  
  if (k == 0) {
    cout<<"No duplicates."<<endl;
  }
}

int main() {
  int phones_sum; char cache[STRLEN];
  int *phones;

  cin>>phones_sum;
  phones = new int[phones_sum]();

  for (int i = 0; i < phones_sum; i++) {
    cin>>cache;

    phones[i] = str_to_phone(cache);
  }

  sort_phones(phones, phones_sum);

  out(phones, phones_sum);

  delete [] phones;

  return 0;
}
