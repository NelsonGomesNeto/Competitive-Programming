#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxH = 1e4 + 1, inf = 1e9; int h, n;
struct Magic
{
  int a, b;
  void read() { scanf("%d %d", &a, &b); }
};
Magic magics[maxN];

lli memo[maxH];

int main()
{
  while (scanf("%d %d", &h, &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      magics[i].read();

    for (int i = 0; i < h; i ++)
      memo[i] = inf;
    memo[h] = 0;
    for (int hh = h; hh >= 0; hh --)
      for (int i = 0; i < n; i ++)
      {
        int res = max(0, hh - magics[i].a);
        memo[res] = min(memo[res], memo[hh] + magics[i].b);
      }
    printf("%lld\n", memo[0]);
  }
  return 0;
}