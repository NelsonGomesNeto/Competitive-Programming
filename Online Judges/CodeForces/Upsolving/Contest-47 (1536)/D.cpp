#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli b[maxN];

int main()
{
  int t;
  int hehe = 0;
  while (~scanf("%d", &t))
  {
    if (hehe++) printf("------------\n");
    for (int tt = 1; tt <= t; tt++)
    {
      int n; scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%lld", &b[i]);

      bool can = true;
      for (int i = 0; i + 3 < n; i++)
        if (b[i] > b[i + 1] && b[i + 1] > b[i + 2] && b[i + 2] < b[i + 3])
          can = false;
        else if (b[i] < b[i + 1] && b[i + 1] < b[i + 2] && b[i + 2] > b[i + 3])
          can = false;

      printf("%s\n", can ? "YES" : "NO");
    }
  }
  return 0;
}
