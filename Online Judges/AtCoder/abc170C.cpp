#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, n;
  while (scanf("%d %d", &x, &n) != EOF)
  {
    set<int> p;
    for (int i = 0; i < n; i++)
    {
      int pp; scanf("%d", &pp);
      p.insert(pp);
    }

    int ans = 10000, diff = 10000;
    for (int i = -10; i <= 110; i++)
      if (!p.count(i))
        if (abs(i - x) < diff)
          ans = i, diff = abs(i - x);
    printf("%d\n", ans);
  }
  return 0;
}