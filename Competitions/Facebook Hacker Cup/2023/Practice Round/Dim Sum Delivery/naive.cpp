#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, m, a, b;

bool Solve(int i = 1, int j = 1, bool alice = true) {
  if (i == n || j == m) return alice;

  bool res;
  if (alice) {
    res = false;
    for (int dn = 1, end = min(a, n - i); dn <= end; ++dn) {
      res = max(res, Solve(i + dn, j, !alice));
    }
  } else {
    res = true;
    for (int dm = 1, end = min(b, m - j); dm <= end; ++dm) {
      res = min(res, Solve(i, j + dm, !alice));
    }
  }
  return res;
}

int main() {
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    bool ans = Solve();
    printf("Case #%d: %s\n", test_case, ans ? "YES" : "NO");
  }
  return 0;
}
