#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, k, m;
int a[maxN];

int main()
{
  while (scanf("%d %d %d", &n, &k, &m) != EOF)
  {
    ldouble mean = 0;
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%d", &a[i]);
      mean += a[i];
    }

    int ans = -1;
    for (int i = 0; i <= k && ans == -1; i ++)
      if ((mean + i) / n >= m)
        ans = i;
    printf("%d\n", ans);
  }
  return 0;
}