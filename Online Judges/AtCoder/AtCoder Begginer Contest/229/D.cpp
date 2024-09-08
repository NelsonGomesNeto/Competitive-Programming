#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
char s[maxN + 1];
int acc[maxN + 1];

int can(int x)
{
  for (int i = 0; i + x - 1 < n; i++)
    if (acc[i + x] - acc[i] <= k)
      return true;
  return false;
}

int main()
{
  while (~scanf(" %s", s))
  {
    scanf("%d", &k);
    n = strlen(s);

    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + (s[i] == '.');

    int lo = 0, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if (can(mid)) lo = mid;
      else hi = mid - 1;
    }
    printf("%d\n", lo);
  }
  return 0;
}