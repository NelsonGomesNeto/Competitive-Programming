#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1;
  }
  return ans;
}
lli inv(lli x) { return modPow(x, mod - 2); }

const int maxN = 1e3; int n, m, k;

struct ModFraction
{
  lli num, div;
  ModFraction operator*(const ModFraction& other) const
  {
    return ModFraction{num * other.num % mod, div * other.div % mod};
  }
  void operator +=(const ModFraction& other)
  {
    // a / b + c / d
    // a*d / b * d + c * b / b * d
    // a*d + c*b / b*d
    num = (num*other.div % mod + other.num*div % mod) % mod;
    div = div * other.div % mod;
    lli g = gcd(num, div);
    if (g == 0) return;
    num /= g, div /= g;
  }
};

bool visited[maxN][maxN];
ModFraction memo[maxN][maxN];
ModFraction solve(int i = 0, int moves = 0)
{
  if (i == n) return ModFraction{1, 1};
  if (moves >= k) return ModFraction{0, 1};
  ModFraction& ans = memo[i][moves];
  if (visited[i][moves]) return ans;
  visited[i][moves] = true;
  // printf("\t%d %d\n", i, moves); fflush(stdout);
  // if (ans.num != -1 && ans.div != -1) return ans;

  ans = ModFraction{0, 1};
  for (int j = 1; j <= m; ++j)
  {
    int delta = n - i;
    int ni = i + j;
    if (delta < j)
      ni = i + delta - (j - delta);
    ans += ModFraction{1, m} * solve(ni, moves + 1);
  }

  return ans;
}

int main()
{
  // while (cin >> n >> m >> k)
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    memset(visited, false, sizeof(visited));
    ModFraction ans = solve();
    DEBUG printf("%lld %lld\n", ans.num, ans.div);
    // y / x
    // x*z == y
    // z = y * inv(x)
    lli res = ans.num * inv(ans.div) % mod;
    printf("%lld\n", res);
  }
  return 0;
}
