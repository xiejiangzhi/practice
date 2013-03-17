#include <iostream>

#include <cstring>

using std::cout;
using std::endl;
using std::cin;

#define MAX_NUMBER  128

class Bignum {
public:

  Bignum(char *str) {
    int str_len = strlen(str) - 1;
    point = 0;

    for (int i = MAX_NUMBER - 1; i >= 0; i--) {
      if (str_len >= 0) {
        if (str[str_len] == '.') {
          point = MAX_NUMBER - i - 1;
          str_len--; i++;
          continue;
        }

        numbers[i] = str[str_len--] - 48;
      } else {
        numbers[i] = 0;  
      }
    }
  }

  Bignum(const Bignum & bg) {
    point = bg.point;

    for (int i = 0; i < MAX_NUMBER; i++) {
      numbers[i] = bg.numbers[i];
    }
  }


  void show() {
    bool start = false;
    int last_zero = 0;

    for (int i = MAX_NUMBER - 1; i >= 0; i--) {
      if (numbers[i] == 0) { last_zero++; }
      else { break; }
    }

    if (last_zero == MAX_NUMBER) {
      cout<<0<<endl;
      return ;
    }

    for (int i = 0; i < MAX_NUMBER; i++) {
      if (MAX_NUMBER - i <= point && MAX_NUMBER - i <= last_zero) {
        break;
      } else if (MAX_NUMBER - i == point) {
        start = true;  cout<<".";
      }

      if ( !start ) {
        if (numbers[i] == 0){ continue; }
        else { start = true; }
      }

      cout<<short(numbers[i]);
    }

    cout<<endl;
  }


  Bignum & pow(int n) {
    if (n <= 0) {
      for (int i = 0; i < MAX_NUMBER - 1; i++) {
        numbers[i] = 0;
      }
      numbers[MAX_NUMBER - 1] = 1;
      point = 0;
    } else {
      Bignum bg = *this;

      while (--n) { *this *= bg; }  
    }

    return *this;
  }


  Bignum & operator*=(const Bignum & bg) {
    char tmp[MAX_NUMBER];
    int tmp_i, a_index = start_index(), b_index = bg.start_index();
    for (int i = 0; i < MAX_NUMBER; i++) {
      tmp[i] = numbers[i];
      numbers[i] = 0;
    }

    for (int i = MAX_NUMBER - 1; i >= a_index; i--) {
      for (int j = MAX_NUMBER - 1; j >= b_index; j--) {
        tmp_i = i - (MAX_NUMBER - 1 - j);

        numbers[tmp_i] += tmp[i] * bg.numbers[j];

        carry(tmp_i);
      }
    }

    point += bg.point;

    return *this;
  }

private:
  char numbers[MAX_NUMBER];
  int point;

  int start_index() const {
    for (int i = 0; i < MAX_NUMBER; i++) {
      if (numbers[i] != 0) { return i; }
    }

    return MAX_NUMBER - 1;
  }

  void carry(int index) {
    do {
      if (numbers[index] < 10) { return ; }

      if (index > 0) { numbers[index - 1] += numbers[index] / 10; }  
      numbers[index] %= 10;
    } while (--index);
  }
};


int main() {
  char number[10]; int n;

  while (cin>>number>>n) {
    Bignum bg = Bignum(number);
    
    bg.pow(n).show();
  }

  return 0;
}
