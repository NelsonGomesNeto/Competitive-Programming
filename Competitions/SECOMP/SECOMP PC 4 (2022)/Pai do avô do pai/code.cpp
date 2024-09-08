#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3;
int n, q;
int parents[maxN];

int main()
{
  parents[0] = -1;
  while (~scanf("%d", &n))
  {
    for (int i = 1; i < n; ++i)
      scanf("%d", &parents[i]);

    scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
      int u, k;
      scanf("%d %d", &u, &k);
      while (k-- && u != -1)
        u = parents[u];
      printf("%d\n", u);
    }
  }
  return 0;
}
