#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 20; int b, n;
int money[maxN];

int main()
{
  while (scanf("%d %d", &b, &n) && !(!b && !n))
  {
    for (int i = 0; i < b; i ++) scanf("%d", &money[i]);

    for (int i = 0; i < n; i ++)
    {
      int d, c, v; scanf("%d %d %d", &d, &c, &v);
      money[d - 1] -= v, money[c - 1] += v;
    }

    bool can = true;
    for (int i = 0; i < b; i ++)
      if (money[i] < 0)
        can = false;
    printf("%c\n", can ? 'S' : 'N');
  }
  return(0);
}