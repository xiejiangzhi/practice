#include <iostream>
#include <cstdlib>
#include <map>


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

void out_phone_sum(int phone, int sum) {
  using std::cout;
  using std::endl;

  cout.width(3);
  cout.fill('0');
  cout.setf(std::ios::right);
  cout<<(phone / 10000)<<"-";

  cout.width(4);
  cout.fill('0');
  cout.setf(std::ios::right);
  cout<<(phone % 10000)<<" ";

  cout<<sum<<endl;
}

void out(std::map<int, int> *phones) {
  std::map<int, int>::iterator iter = phones->begin(), end = phones->end();
  int sum = 0;

  for (; iter != end; iter++) {
    if (iter->second > 1) { 
      out_phone_sum(iter->first, iter->second);
      sum++;
    }
  }

  if (sum == 0) {
    std::cout<<"No duplicates."<<std::endl;
  }
}

int main() {
  using std::cin;
  using std::map;

  int phones_sum; char cache[STRLEN];
  map<int, int> phones;

  cin>>phones_sum;

  for (int i = 0; i < phones_sum; i++) {
    cin>>cache;

    phones[str_to_phone(cache)] += 1;
  }

  out(&phones);
  
  return 0;
}
