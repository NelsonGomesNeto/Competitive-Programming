#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
n = 20
2^n = 1e6

*/

struct TestCase {

int n;
int full_mask;
vector<int> a;

int Brute() {
  sort(a.begin(), a.end());

  int ans = 0;
  do {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      int g = a[0];
      for (int j = 1; j <= i; ++j)
        g = gcd(g, a[j]);
      sum += g;
    }
    if (sum > ans) {
      printf("best:");
      for (int aa : a) printf(" %d", aa);
      printf("\n");
    }
    ans = max(ans, sum);
  } while (next_permutation(a.begin(), a.end()));

  return ans;
}

vector<lli> memo;
lli Solve(int mask = 0, int g = 0) {
  if (mask == full_mask) return g;
  lli& ans = memo[mask];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = 0; j < n; ++j)
    if (!((mask >> j) & 1)) {
      ans = max(
        ans,
        Solve(mask | (1 << j), mask == 0 ? a[j] : gcd(g, a[j]))
      );
    }
  ans += g;

  return ans;
}

void Run() {
  scanf("%d", &n);
  full_mask = (1 << n) - 1;
  a.resize(n);
  for (int& aa : a) scanf("%d", &aa);

  memo.resize(1 << n, -1);
  lli ans = Solve();
  printf("%lld\n", ans);
}

};
TestCase test_case;

int main()
{
  test_case = TestCase();
  test_case.Run();

  return 0;
}
