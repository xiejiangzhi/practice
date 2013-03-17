#include <iostream>
#include <cstdlib>

#define  DAY              4
#define  MONTH            8
#define  HAAB_MONTHS      19
#define  TZOLKIN_NAMES    20
#define  TZOLKIN_NAMELEN  10
#define  TZOLKIN_MONTH    20
#define  TZOLKIN_YEAR     (TZOLKIN_MONTH * 13)

int identifier(const char * str) {
  int tmp = 123456789;

  for (int i = 0; str[i]; i++) {
    tmp += str[i] * (tmp << 3);
  }

  return tmp;
}


class Haab {
public:
  Haab(char *day, char* month, int year) {
    days = atoi(day) + month_to_days(month) + year_to_days(year);
  }

  int year_to_days(int year) {
    return year * 365;
  }

  int month_to_days(char * month) {
    int tmp = identifier(month), m_day = 0;

    for (int i = 0; i < HAAB_MONTHS; i++) {
      if (MONTHS[i] == tmp) { m_day = i * 20; }
    }

    return m_day;
  }

  void out_tzolkin() {
    int year = days / TZOLKIN_YEAR;
    int tmp = days % TZOLKIN_YEAR;

    std::cout<<(tmp % 13 + 1)<<" "<<TMONTH_NAMES[(tmp % 20)]<<" "<<year<<std::endl;
  }

  static const int MONTHS[HAAB_MONTHS];
  static const char TMONTH_NAMES[TZOLKIN_NAMES][TZOLKIN_NAMELEN];
private:
  int days;
};

const int Haab::MONTHS[HAAB_MONTHS] = {
  identifier("pop"),    identifier("no"),     identifier("zip"),
  identifier("zotz"),   identifier("tzec"),   identifier("xul"),
  identifier("yoxkin"), identifier("mol"),    identifier("chen"),
  identifier("yax"),    identifier("zac"),    identifier("ceh"),
  identifier("mac"),    identifier("kankin"), identifier("muan"),
  identifier("pax"),    identifier("koyab"),  identifier("cumhu"),
  identifier("uayet")
};

const char Haab::TMONTH_NAMES[TZOLKIN_NAMES][TZOLKIN_NAMELEN] = {
  "imix",   "ik",     "akbal",  "kan",   "chicchan",
  "cimi",   "manik",  "lamat",  "muluk", "ok",
  "chuen",  "eb",     "ben",    "ix",    "mem",
  "cib",    "caban",  "eznab",  "canac", "ahau"
};

int main() {
  using std::cin;

  int data_sum;
  cin>>data_sum; std::cout<<data_sum<<std::endl;
  
  char day[DAY], month[MONTH]; int year;

  for (int i = 0; i < data_sum; i++) {
    cin>>day>>month>>year;

    Haab(day, month, year).out_tzolkin();
  }

  return 0;
}
