#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int a[2*maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    int odds = 0;
    for (int i = 0; i < 2*n; i++)
    {
      scanf("%d", &a[i]);
      odds += a[i] & 1;
    }

    DEBUG printf("\t%d\n", odds);
    bool can = odds == n;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
