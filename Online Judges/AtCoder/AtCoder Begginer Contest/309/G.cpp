#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;

const int maxN = 100;
int n, x;
lli fact[maxN + 1];

struct State
{
  int i;
  unordered_set<int> has;

  State next(int a)
  {
    State newState{i + 1, has};
    newState.has.insert(a);
    return newState;
  }
};

lli solve(State s = State{0, {}})
{
  if (s.i == n) return 1;

  lli ans = 0;
  for (int j = 0; j < n; ++j)
    if (abs(s.i - j) >= x && !s.has.count(j))
      ans = (ans + solve(s.next(j)));

  return ans;
}

int main()
{
  fact[0] = 1;
  for (int i = 1; i <= maxN; ++i)
    fact[i] = fact[i] * (i - 1) % mod;

  while (~scanf("%d %d", &n, &x))
  {
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
