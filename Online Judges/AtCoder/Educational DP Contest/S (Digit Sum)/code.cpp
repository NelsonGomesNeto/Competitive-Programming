#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4, maxD = 100; int n, d;
const lli mod = 1e9 + 7;
char k[maxN + 1];

lli memo[maxN][maxD][2];
lli solve(int i = 0, int rem = 0, bool smaller = false)
{
  if (i == n) return rem == 0;
  lli &ans = memo[i][rem][smaller];
  if (ans != -1) return ans;

  ans = 0;
  for (char digit = '0'; digit <= (smaller ? '9' : k[i]); digit++)
    ans = (ans + solve(i + 1, (rem + (digit - '0')) % d, smaller | (digit < k[i]))) % mod;

  return ans;
}

int main()
{
  while (scanf(" %s", k) != EOF)
  {
    scanf("%d", &d);
    n = strlen(k);

    DEBUG printf("%s - %d\n", k, d);

    memset(memo, -1, sizeof(memo));
    lli ans = (solve() - 1 + mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}