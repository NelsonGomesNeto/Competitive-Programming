#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = 1e13;
const int kMaxN = 100, kMaxK = 5;
int n, k, p;
int a[kMaxN][kMaxK];
lli c[kMaxN];

struct State {
  State(int i = 0, vector<int> params = vector<int>(k, 0)) : i(i), params(params) {
  }

  int i;
  vector<int> params;

  bool Valid() {
    for (int j = 0; j < k; ++j)
      if (params[j] < p)
        return false;
    return true;
  }

  State Next() {
    return State(i + 1, params);
  }

  State Buy() {
    State new_state = State(i + 1, params);
    for (int j = 0; j < k; ++j)
      new_state.params[j] = min(p, new_state.params[j] + a[i][j]);
    return new_state;
  }

  bool operator<(const State& other) const {
    return i < other.i || (i == other.i && params < other.params);
  }
};

map<State, lli> memo;
lli Solve(State s = State()) {
  if (s.i == n) return s.Valid() ? 0 : inf;
  if (memo.count(s)) return memo[s];
  lli& ans = memo[s];

  ans = min(Solve(s.Next()), Solve(s.Buy()) + c[s.i]);
  return ans;
}

int main() {
  while (~scanf("%d %d %d", &n, &k, &p)) {
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &c[i]);
      for (int j = 0; j < k; ++j)
        scanf("%d", &a[i][j]);
    }

    memo.clear();
    lli ans = Solve();
    if (ans == inf) ans = -1;
    printf("%lld\n", ans);
  }
  return 0;
}
