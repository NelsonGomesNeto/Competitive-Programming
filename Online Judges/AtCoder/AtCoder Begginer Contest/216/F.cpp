#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;
const lli mod = 998244353;
struct Ab
{
  int a, b;
  bool operator<(const Ab &other) const { return a < other.a; }
};
Ab ab[maxN];
int limit[maxN];

lli memo[maxN][maxN + 1];
lli cnt(int i, int budget)
{
  if (budget < 0) return 0;
  if (i == -1) return 1;
  lli &ans = memo[i][budget];
  if (ans != -1) return ans;

  ans = (cnt(i - 1, budget) + cnt(i - 1, budget - ab[i].b)) % mod;
  return ans;
}

lli pot2[maxN + 1];

int main()
{
  pot2[0] = 1;
  for (int i = 1; i <= maxN; i++)
    pot2[i] = pot2[i - 1] * 2LL % mod;

  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &ab[i].a);
    for (int i = 0; i < n; i++)
      scanf("%d", &ab[i].b);
    sort(ab, ab+n);

    memset(memo, -1, sizeof(memo));
    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      lli c = cnt(i - 1, ab[i].a - ab[i].b), p = pot2[i + 1];
      DEBUG printf("\t%d - %lld %lld\n", i, c, p);
      ans = (ans + c % mod) % mod;
    }

    printf("%lld\n", ans);
  }
  return 0;
}