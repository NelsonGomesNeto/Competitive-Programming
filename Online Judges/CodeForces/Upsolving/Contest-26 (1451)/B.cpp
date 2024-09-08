#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, q;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &q);
    scanf(" %s", s);

    while (q--)
    {
      int lo, hi; scanf("%d %d", &lo, &hi); lo--, hi--;

      bool can = false;
      for (int i = 0; i < lo; i++)
        can |= s[i] == s[lo];
      for (int i = hi + 1; i < n; i++)
        can |= s[i] == s[hi];
      printf("%s\n", can ? "YES" : "NO");
    }
  }
  return 0;
}
