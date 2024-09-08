#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
char ss[kMaxN + 1];
string s;

multiset<int> Read(const string& input) {
  multiset<int> numbers;
  int a;

  int prv = 0;
  for (int p = input.find(' '); p != input.npos; p = input.find(' ', prv)) {
    if (p == prv) {
      ++prv;
      continue;
    };
    DEBUG printf("\t%d %d\n", p, prv);
    sscanf(input.substr(prv, p - prv).c_str(), "%d", &a);
    numbers.insert(a);
    prv = p + 1;
  }
  sscanf(input.substr(prv).c_str(), "%d", &a);
  numbers.insert(a);

  return numbers;
}

pair<multiset<int>, multiset<int>> Parse(const string& input) {
  int two_points = input.find(":");
  int pipe = input.find("|");
  string l = input.substr(two_points + 2, pipe - two_points - 3);
  string r = input.substr(pipe + 2);

  multiset<int> winning_numbers = Read(l), bets = Read(r);
  DEBUG {
    printf("\t||");
    for (int a : winning_numbers)
      printf(" %d", a);
    printf("\n");
    printf("\t||");
    for (int a : bets)
      printf(" %d", a);
    printf("\n");
  }

  return make_pair(winning_numbers, bets);
}

int main() {
  int ans = 0;
  while (~scanf(" %[^\n]", ss)) {
    s = string(ss);

    auto [winning_numbers, bets] = Parse(s);
    int cnt = 0;
    for (int b : bets) {
      cnt += winning_numbers.count(b) != 0;
    }

    int res = 0;
    if (cnt)
      res = pow(2, cnt - 1);

    ans += res;
  }
  printf("%d\n", ans);
  return 0;
}
