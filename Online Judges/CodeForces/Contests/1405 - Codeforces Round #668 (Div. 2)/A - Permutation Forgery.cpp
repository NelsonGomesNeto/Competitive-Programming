#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int p[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

      reverse(p, p+n);
      for (int i = 0; i < n; i++)
        printf("%d%c", p[i], i < n - 1 ? ' ' : '\n');
    }
  return 0;
}