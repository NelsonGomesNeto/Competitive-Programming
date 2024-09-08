#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2;
int n, d;
int t[maxN];

int main()
{
  while (~scanf("%d %d", &n, &d))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &t[i]);

    int ans = -1;
    for (int i = 1; i < n; ++i)
      if (t[i] - t[i - 1] <= d)
      {
        ans = t[i];
        break;
      }
    printf("%d\n", ans);
  }
  return 0;
}
