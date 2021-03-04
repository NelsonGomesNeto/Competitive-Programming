#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  from u, can go to every edge v such that
  v - u = k, and u & k == k
  Every combination of u's ones (in binary representation)

  v can't have any setted bit on the right of u's setted bits
*/

bool can(lli u, lli v)
{
  if (u > v) return false;

  while (u < v)
  {
    bool done = false;
    for (int i = 29; i >= 0; i--)
    {
      lli p = 1LL << i;
      if ((u & p) && u + p <= v)
      {
        u += p;
        done = true;
        break;
      }
    }
    if (!done)
      return false;
  }

  return u == v;
}

int main()
{
  int q; scanf("%d", &q);
  for (int i = 0; i < q; i++)
  {
    lli u, v; scanf("%lld %lld", &u, &v);
    printf("%s\n", can(u, v) ? "YES" : "NO");
  }
  return 0;
}