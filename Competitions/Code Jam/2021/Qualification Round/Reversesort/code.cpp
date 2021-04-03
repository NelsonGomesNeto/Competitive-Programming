#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int l[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &l[i]);

    int ans = 0;
    for (int i = 0; i + 1 < n; i++)
    {
      int idx;
      for (int j = i; j < n; j++)
        if (l[j] == i + 1)
        {
          idx = j;
          break;
        }
      reverse(l+i, l+idx+1);
      ans += idx - i + 1;
    }
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}