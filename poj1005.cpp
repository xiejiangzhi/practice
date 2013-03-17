#include <iostream>
#include <cmath>


#define PI  3.14159265

int has_year(double x, double y) {
  int sum = 0;
  double len = sqrt(pow(fabs(x), 2) + pow(y, 2));

  while (sqrt((sum * 50 * 2) / PI) < len) { sum += 1; }

  return sum;
}


int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  int sum_point; double x, y;


  cin>>sum_point;

  for (int i = 0; i < sum_point; i++) {
    cin>>x>>y;

    cout<<"Property "<<i + 1<<": This property will begin eroding in year "
    <<has_year(x, y)<<"."<<endl;
  }

  cout<<"END OF OUTPUT."<<endl;

  return 0;
}
