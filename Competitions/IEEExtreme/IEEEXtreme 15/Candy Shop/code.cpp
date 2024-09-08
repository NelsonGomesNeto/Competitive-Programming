#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1 - 1 bags * 2
2 - 1 bags * 1
3 - 2 bags * 1

target: 2

I should only consider combinations from types I've already processed
0 1 2 3 4 5
0 2 2

1
2, 3
3, 3
*/

const int maxN = 1e5; int n, k;
const lli mod = 998244353;
int a[maxN], b[maxN];

lli memo[maxN + 1];
lli memo2[maxN + 1];
lli pmemo[maxN + 1];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i <= k; i++) memo[i] = memo2[i] = 0;

    for (int i = 0; i < n; i++)
      scanf("%d %d", &a[i], &b[i]);

    for (int i = 0; i < n; i++)
    {
      for (int s = 1; s <= k; s++)
        memo[s] = (memo[s] + memo[s - 1]) % mod;

      for (int aa = 1; aa <= a[i] && (lli)aa * b[i] <= k; aa++)
      {
        int c = aa * b[i];
        memo[c]++;
      }
    }

    DEBUG {
      for (int s = 1; s <= k; s++)
        printf("\t%d - %lld\n", s, memo[s]);
    }

    printf("%lld\n", memo[k]);
  }
  return 0;
}