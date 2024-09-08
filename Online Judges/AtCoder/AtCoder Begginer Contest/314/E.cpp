#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble inf = numeric_limits<ldouble>().max();
const int maxN = 100, maxRep = 100;
int n, m;
struct Roulette {
  int c;
  int not_zero;
  vector<int> s;
  vector<pair<int, ldouble>> lol;
  void read() {
    scanf("%d", &c);
    int p;
    scanf("%d", &p);
    s.clear();
    s.resize(p);

    not_zero = 0;
    map<int, int> cnt;
    for (int& ss : s) {
      scanf("%d", &ss);
      ++cnt[ss];
      not_zero += ss != 0;
    }

    lol.clear();
    for (auto [a, b] : cnt) {
      lol.emplace_back(a, (ldouble)b / p);
    }
  }
};
Roulette roulettes[maxN];

ldouble memo[maxN + 1][maxRep + 1];
ldouble solve(int score = 0, int rep = 0) {
  if (score >= m) return 0;
  if (rep == maxRep) return 0;
  ldouble& ans = memo[score][rep];
  if (ans != -1) return ans;

  ans = inf;
  for (int i = 0; i < n; ++i) {
    ldouble res = 0;
    for (auto [s, prob] : roulettes[i].lol) {
      if (s == 0) {
        res += (double)prob / roulettes[i].not_zero * roulettes[i].c;
      } else {
        res += prob * (solve(score + s, s == 0 ? rep + 1 : 0) + roulettes[i].c);
      }
    }
    ans = min(ans, res);
  }

  return ans;
}
ldouble solve2() {
  for (int i = 0; i <= maxRep; ++i)
    memo[m][i] = 0;

  for (int score = m - 1; score >= 0; --score) {
    for (int rep = maxRep - 1; rep >= 0; --rep) {
      ldouble& ans = memo[score][rep];
      ans = inf;
      for (int i = 0; i < n; ++i) {
        ldouble res = 0;
        for (auto [s, prob] : roulettes[i].lol)
          res += prob * (memo[min(m, score + s)][s == 0 ? rep + 1 : 0] + roulettes[i].c);
        ans = min(ans, res);
      }
    }
  }
  return memo[0][0];
}

int main()
{
  while (~scanf("%d %d", &n, &m)) {
    for (int i = 0; i < n; ++i)
      roulettes[i].read();

    for (int i = 0; i <= m; ++i)
      fill(memo[i], memo[i]+maxRep+1, -1);

    ldouble ans = solve();
    printf("%.16Lf\n", ans);
  }
  return 0;
}
