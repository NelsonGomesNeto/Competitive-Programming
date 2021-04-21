#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e6 + 5; int n, a, b;
const ldouble eps = 1e-13;
ldouble sz, p;

ldouble zeroSumP, zeroSumPk;
ldouble memo[maxN + 1];
ldouble memo2[maxN + 1];
ldouble solve(int i = 0)
{
  if (i >= n) return 0;
  ldouble &ans = memo[i];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = a; j <= b; j++)
  {
    ldouble res = solve(i + j);
    ans += p * (1 + res + zeroSumPk + res*zeroSumP);
  }
  return ans;
}
ldouble suffix[maxN + 1];
ldouble solve2()
{
  for (int i = 0; i <= maxN; i++) memo[i] = suffix[i] = 0;

  for (int i = n - 1; i >= 0; i--)
  {
    // for (int j = a + (a == 0); j <= b; j++)
    // {
    //   ldouble res = memo[i + j];
    //   memo[i] += p * (1 + res + zeroSumPk + res*zeroSumP);
    // }
    // p * (1 + a + zeroSumPk + a*zeroSumP)
    // p * (1 + b + zeroSumPk + b*zeroSumP)

    // p + p*res + p*zeroSumPk + p*res*zeroSumP

    ldouble resSum = suffix[i + a] - suffix[i + b + 1];
    memo[i] = p * (1 + resSum + zeroSumPk + resSum*zeroSumP);

    suffix[i] = suffix[i + 1] + memo[i];
  }

  return sz*memo[0];
}

int main()
{
  scanf("%d %d %d", &n, &a, &b);
  sz = b - a + 1;
  p = 1 / sz;

  zeroSumP = 0;
  zeroSumPk = 0;
  if (a == 0)
  {
    ldouble curr = 1;
    for (int i = 2; curr > eps; i++)
    {
      curr *= p;
      zeroSumP += curr;
      zeroSumPk += curr * i;
      // printf("%d - %lf %lf\n", i, curr, curr * i);
    }
  }
  DEBUG printf("%Lf %Lf %Lf\n", zeroSumP, zeroSumPk, p);

  if (a == 0) sz--, a++;

  // for (int i = 0; i <= maxN; i++) memo[i] = -1;
  // ldouble ans = solve();
  ldouble ans2 = solve2();
  // printf("%.15Lf %.15Lf\n", ans, ans2);
  printf("%.15Lf\n", ans2);
  return 0;
}