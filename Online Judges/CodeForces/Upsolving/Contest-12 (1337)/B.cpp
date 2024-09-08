#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int x, n, m; scanf("%d %d %d", &x, &n, &m);
    while (n-- && x > 20)
    {
      x = (x >> 1) + 10;
    }
    while (m--)
    {
      x -= 10;
    }
    printf("%s\n", x > 0 ? "NO" : "YES");
  }
  return 0;
}
