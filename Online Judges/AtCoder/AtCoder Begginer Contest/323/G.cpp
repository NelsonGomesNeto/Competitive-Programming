#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
connect all vertices with n - 1 edges <=> tree (always!)

I just need to find n - 1 edges where: u < v && p[u] > p[v]
*/

const lli mod = 998244353;
const int kMaxN = 5e2;
int n;

int p[kMaxN];

int k;
map<tuple<int, int, int, int>, map<int, lli>> memo;
// vector<lli> nil, one[kMaxN];
map<int, lli> nil, one[kMaxN];
vector<lli> Merge(const vector<lli>& a, const vector<lli>& b) {
  vector<lli> res = a;
  for (int i = 0; i < n; ++i)
    res[i] = (res[i] + b[i]) % mod;
  return res;
}
map<int, lli> Merge(const map<int, lli>& a, const map<int, lli>& b) {
  map<int, lli> res = a;
  for (auto [k, v] : b)
    res[k] = (res[k] + v) % mod;
  return res;
}
map<int, lli> Solve(int i = 0, int j = 0, int edges = 0, int inversions = 0) {
  if (edges >= n) return nil;
  if (inversions > 0) return nil;
  if (i == n) {
    assert(inversions < n);
    return edges == n - 1 ? one[inversions] : nil;
  }

  tuple<int, int, int, int> now{i, j, edges, inversions};
  if (memo.count(now)) return memo[now];
  map<int, lli>& ans = memo[now];

  if (i == j) {
    ans = Solve(i + 1, 0, edges, inversions);
  } else {
    ans = Merge(Solve(i, j + 1, edges + 1, inversions + (p[j] > p[i])), Solve(i, j + 1, edges, inversions));
  }
  return ans;
}

void Reset() {
  nil.clear();
  for (int i = 0; i < n; ++i) {
    one[i] = nil;
    one[i][i] = 1;
  }
  memo.clear();
  // for (int i = 0; i < n; ++i)
  //   for (int j = 0; j < n; ++j)
  //     memo[i][j].clear();
      // for (int t = 0; t < 50; ++t)
        // memo[i][j][t].clear();
}

int main() {
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i]);
      --p[i];
    }

    Reset();
    map<int, lli> res = Solve();
    for (int i = 0; i < n; ++i) {
      printf("%lli%c", res[i], i + 1 < n ? ' ' : '\n');
    }

  }
  return 0;
}
