#include <iostream>

using std::cout;
using std::cin;

#define COINS_COUNT 12
#define LITTLE_CONIN COINS_COUNT / 2 + 1
#define RESULT_STR_LEN 5

#define ALL_TRUE  'e'

#define UNKNOW  0

// loca
#define LEFT    1
#define RIGHT   2

// weight
#define GOOD    1
#define UP      'u'
#define DOWN    'd'


struct Coin {
  int loca;
  int weight;
};

void identification();

int main() {
  int sum;

  cin>>sum;

  for (; sum > 0; sum --) {
    identification();
  }
}



void even_check(Coin *coins, char *left, char *right, char status);
void no_even_check(Coin *coins, char *left, char *right, char status);
void display(Coin *coins);



void identification() {
  char coins_str[2][LITTLE_CONIN], status[RESULT_STR_LEN];
  int tmp;
  Coin coins[COINS_COUNT];

  for (int i = 0; i < COINS_COUNT; i++) {
    coins[i].loca = UNKNOW;
    coins[i].weight = UNKNOW;
  }

  for (int i = 0; i < 3; i++) {
    cin>>coins_str[0]>>coins_str[1]>>status;

    if (status[0] == ALL_TRUE) {
      even_check(coins, coins_str[0], coins_str[1], status[0]);
    } else {
      no_even_check(coins, coins_str[0], coins_str[1], status[0]);
    }
  }

  display(coins);
}




void even_check(Coin *coins, char *left, char *right, char status) {
  for (int i = 0; left[i]; i++) {
    coins[int(left[i]) - 65].weight = GOOD;
  }

  for (int i = 0; right[i]; i++) {
    coins[int(right[i]) - 65].weight = GOOD;
  }
}



void branch_check(Coin *coins, char* coin_names, int loca, char status);
bool include_str(char c, char *left, char *right);

void no_even_check(Coin *coins, char *left, char *right, char status) {
  branch_check(coins, left, LEFT, status);
  branch_check(coins, right, RIGHT, status);

  for (int i = 0; i < COINS_COUNT; i++) {
    if (include_str(i + 65, left, right) == false) {
      coins[i].weight = GOOD;
    }
  }
}

bool include_str(char c, char *left, char *right) {
  for (int i = 0; left[i]; i++) {
    if (left[i] == c) { return true; }
  }

  for (int i = 0; right[i]; i++) {
    if (right[i] == c) { return true; } 
  }

  return false;
}

void branch_check(Coin *coins, char *coin_names, int loca, char status) {
  for (int i = 0; coin_names[i]; i++) {
    Coin &coin = coins[int(coin_names[i]) - 65];
    if (coin.weight == GOOD) { continue; }

    if (coin.loca == loca && coin.weight != status ) {
      coin.weight = GOOD;
      continue;
    }

    if (coin.loca != loca && coin.weight == status) {
      coin.weight = GOOD;
      continue;
    }
    
    coin.loca = loca;
    coin.weight = status;
  }
}



void display(Coin *coins) {
  for (int i = 0; i < COINS_COUNT; i++) {
    if (coins[i].weight != GOOD) {
      Coin &coin = coins[i];
      cout<<char(i + 65)<<" is the counterfeit coin and it is ";

      if (coin.loca == LEFT) {
        cout<<(coin.weight == DOWN ? "light" : "heavy")<<".\n";
      } else {
        cout<<(coin.weight == UP ? "light" : "heavy")<<".\n";
      }
    }
  }
}
