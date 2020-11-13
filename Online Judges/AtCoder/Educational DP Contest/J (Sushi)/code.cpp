#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e2; int n, total;
const double eps = 1e-12;
const int inf = 1e7 / 3e2;
int cnt[4];

double sumZeroPk[maxN], sumZeroP[maxN];
// p + p*ans + sum(i = [1, inf], p * zp^i * (i + 1) + p * zp^i * ans)
// p + p*ans + p*sum(zp^i * (i + 1) + zp^i * ans)
// p*(1 + ans + sum(zp^i * (i + 1)) + ans*sum(zp^i))
// zp^i * (i + 1) <- store sum (sumZeroP)
// zp^i <- store sum (sumZeroPk)

double memo[maxN + 1][maxN + 1][maxN + 1];
double solve(int one = cnt[1], int two = cnt[2], int three = cnt[3])
{
  if (one + two + three == 0) return 0;
  double &ans = memo[one][two][three];
  if (ans != -1) return ans;

  int zero = n - (one + two + three);
  double zeroP = (double)zero / n;
  double oneP = (double)one / n;
  double twoP = (double)two / n;
  double threeP = (double)three / n;
  ans = 0;

  double oneAns = one ? solve(one - 1, two, three) : 0;
  double twoAns = two ? solve(one + 1, two - 1, three) : 0;
  double threeAns = three ? solve(one, two + 1, three - 1) : 0;

  // if (one) ans += oneP * (1 + oneAns);
  // if (two) ans += twoP * (1 + twoAns);
  // if (three) ans += threeP * (1 + threeAns);
  // double curr = 1;
  // for (int k = 2; curr > eps; k++)
  // {
  //   curr *= zeroP;
  //   if (one) ans += oneP * curr * (k + oneAns);
  //   if (two) ans += twoP * curr * (k + twoAns);
  //   if (three) ans += threeP * curr * (k + threeAns);
  // }

  if (one) ans += oneP * (1 + oneAns + sumZeroPk[zero] + oneAns*sumZeroP[zero]);
  if (two) ans += twoP * (1 + twoAns + sumZeroPk[zero] + twoAns*sumZeroP[zero]);
  if (three) ans += threeP * (1 + threeAns + sumZeroPk[zero] + threeAns*sumZeroP[zero]);

  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    // zp^i * (i + 1) <- store sum
    // zp^i <- store sum
    sumZeroP[0] = sumZeroPk[0] = 0;
    for (int i = 1; i < n; i++)
    {
      sumZeroP[i] = sumZeroPk[i] = 0;
      double curr = 1, zeroP = (double)i / n;
      for (int k = 2; curr > eps; k++)
      {
        curr *= zeroP;
        sumZeroP[i] += curr;
        sumZeroPk[i] += curr * k;
      }
    }

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      int a; scanf("%d", &a);
      cnt[a]++;
    }

    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= n; j++)
        for (int k = 0; k <= n; k++)
          memo[i][j][k] = -1;
    double ans = solve();
    printf("%.15lf\n", ans);
  }
  return 0;
}