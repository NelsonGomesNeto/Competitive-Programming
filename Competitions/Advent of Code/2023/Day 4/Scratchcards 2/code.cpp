#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
char ss[kMaxN + 1];
string s;
map<int, lli> out;

multiset<int> Read(const string& input) {
  multiset<int> numbers;
  int a;

  int prv = 0;
  for (int p = input.find(' '); p != input.npos; p = input.find(' ', prv)) {
    if (p == prv) {
      ++prv;
      continue;
    };
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

  return make_pair(winning_numbers, bets);
}

int main() {
  lli ans = 0, curr = 1;
  for (int i = 0; ~scanf(" %[^\n]", ss); ++i) {
    s = string(ss);

    auto [winning_numbers, bets] = Parse(s);
    int cnt = 0;
    for (int b : bets) {
      cnt += winning_numbers.count(b) != 0;
    }

    DEBUG printf("\t%d %lld %d\n", i, curr, cnt);
    ans += curr;

    if (cnt) {
      const lli to_add = curr;
      curr += to_add;
      out[i + cnt] += to_add;
    }

    auto it = out.find(i);
    if (it != out.end()) {
      DEBUG printf("\t\t%lld\n", it->second);
      curr -= it->second;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
