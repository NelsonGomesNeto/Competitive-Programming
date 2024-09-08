#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
char ss[kMaxN + 1];
string s;

vector<pair<string, int>> number_map = {
  {"1", 1},
  {"2", 2},
  {"3", 3},
  {"4", 4},
  {"5", 5},
  {"6", 6},
  {"7", 7},
  {"8", 8},
  {"9", 9},
  {"one", 1},
  {"two", 2},
  {"three", 3},
  {"four", 4},
  {"five", 5},
  {"six", 6},
  {"seven", 7},
  {"eight", 8},
  {"nine", 9},
};

int TryAll(int i) {
  for (auto& [sub, number] : number_map) {
    if (i + sub.size() <= s.size() && sub == s.substr(i, sub.size())) {
      return number;
    }
  }
  return -1;
}

int ReadNumber() {
  vector<int> digits;
  for (int i = 0; i < s.size(); ++i) {
    int number = TryAll(i);
    if (number == -1) continue;
    digits.push_back(number);
  }
  assert(!digits.empty());
  return digits[0] * 10 + digits.back();
}

int main() {
  int ans = 0;
  while (~scanf(" %s", ss)) {
    s = string(ss);
    ans += ReadNumber();
  }
  printf("%d\n", ans);

  return 0;
}
