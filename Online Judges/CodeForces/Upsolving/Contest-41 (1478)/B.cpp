#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a; int d;
bool isLucky(lli aux = a)
{
  while (aux)
  {
    if (aux % 10 == d)
      return true;
    aux /= 10;
  }
  return false;
}
int digits(lli aux = a)
{
  int d = aux == 0;
  while (aux)
  {
    d++;
    aux /= 10;
  }
  return d;
}

// bool solve(int i = digits() - 1, bool equal = true, bool had = false)
// {
//   if (i == -1)
//   {
//     return ?;
//   }
// }

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    bool ans[10][10]; memset(ans, false, sizeof(ans));
    int q; scanf("%d %d", &q, &d);

    for (int i = 10; i <= 100; i++)
    {
      a = i;
      bool can = isLucky(a);
      for (lli j = 1; j * d < a; j++)
        ans[a % d][(a - d * j) % d] = isLucky(a - d * j);
    }

    while (q--)
    {
      scanf("%lld", &a);
      bool can = isLucky(a);
      for (lli j = 1; j * d < a && j < 100; j++)
        can |= isLucky(a - d * j);
      printf("%s\n", can ? "YES" : "NO");
      // printf("%s\n", *max_element(ans[a % d], ans[a % d] + 10) ? "YES" : "NO");
    }
  }
  return 0;
}
