#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
char s[maxN + 1];
int flips[maxN], l[maxN];
// r - ends at even or odd position - ends at even or odd counter
lli r[2][2][maxN];

int main()
{
  while (scanf("%s", s) != EOF)
  {
    memset(flips, 0, sizeof(flips)), memset(r, 0, sizeof(r));
    getchar();
    n = strlen(s);

    for (int i = 1; i < n; i ++)
      if (s[i - 1] != s[i])
        flips[i] = true;

    for (int i = 1; i < n; i ++)
      l[i] = l[i - 1] + flips[i];

    r[(n - 1) & 1][l[n - 1] & 1][n - 1] = 1;
    for (int i = n - 2; i >= 0; i --)
    {
      for (int j = 0; j < 2; j ++)
        for (int k = 0; k < 2; k ++)
          r[j][k][i] = r[j][k][i + 1];
      r[i & 1][l[i] & 1][i] ++;
    }
    DEBUG
      for (int i = 0; i < n; i ++)
        printf("%d - %lld %lld %lld %lld\n", i, r[0][0][i], r[0][1][i], r[1][0][i], r[1][1][i]);

    lli even = 0, odd = 0;
    for (int i = 0; i < n; i ++)
    {
      even += r[!(i & 1)][l[i] & 1][i];
      odd += r[i & 1][l[i] & 1][i];
    }
    printf("%lld %lld\n", even, odd);
  }
  return 0;
}