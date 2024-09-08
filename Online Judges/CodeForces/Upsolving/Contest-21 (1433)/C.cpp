#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli biggest = *max_element(a, a+n);
    int pos = -2;
    for (int i = 0; i < n; i++)
      if (a[i] == biggest && ((i && a[i - 1] < biggest) || (i + 1 < n && a[i + 1] < biggest)))
        pos = i;

    printf("%d\n", pos + 1);
  }
  return 0;
}
