#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bool solve(int i = 0, lli a0 = 4132, lli a1 = 5123)
{
  if (a0 == -4132 && a1 == -5123) return true;
  if (i == 6) return false;

  if (solve(i + 1, a0 + a1, a1))
  {
    printf("1\n");
    return true;
  }
  if (solve(i + 1, a0, a1 - a0))
  {
    printf("2\n");
    return true;
  }
  return false;
}

int main()
{
  // solve();

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    printf("%d\n", 6*(n / 2));
    for (int i = 0; i < n; i += 2)
    {
      printf("2 %d %d\n", i + 1, i + 2);
      printf("1 %d %d\n", i + 1, i + 2);
      printf("1 %d %d\n", i + 1, i + 2);
      printf("2 %d %d\n", i + 1, i + 2);
      printf("1 %d %d\n", i + 1, i + 2);
      printf("1 %d %d\n", i + 1, i + 2);
    }
  }
  return 0;
}
