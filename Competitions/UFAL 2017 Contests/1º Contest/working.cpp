#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int big[n], small[m];
  for (int i = 0; i < n; i ++)
    scanf("%d", &big[i]);
  for (int i = 0; i < m; i ++)
    scanf("%d", &small[i]);

  sort(big, big+n); sort(small, small+m);

  int changes = 0, lo = 0, hi = m - 1;

  while (small[m - 1] > big[0])
  {
    int ds = hi - 1 >= 0 ? small[hi] - small[hi - 1] : 0, db = lo + 1 < n ? big[lo + 1] - big[lo] : 0;
    DEBUG printf("At: %d %d (%d %d) [%d %d]\n", lo, hi, big[lo], small[hi], db, ds);
    if (hi - 1 >= 0 && lo + 1 < n)
      if (ds < db || (ds == db && m < n))
      {
        changes += ds;
        small[hi] -= ds;
        hi --;
      }
      else
      {
        changes += db;
        big[lo] += db;
        lo ++;
      }
    else if (hi - 1 >= 0)
    {
      changes += ds;
      small[hi] -= ds;
      hi --;
    }
    else
    {
      changes += db;
      big[lo] += db;
      lo ++;
    }
    if (lo == n - 1 && hi == 0)
    {
      lo = 0; hi = m - 1;
    }
  } DEBUG printf("At: %d %d (%d %d)\n", lo, hi, big[lo], small[hi]);

  printf("%d\n", changes);

  return(0);
}