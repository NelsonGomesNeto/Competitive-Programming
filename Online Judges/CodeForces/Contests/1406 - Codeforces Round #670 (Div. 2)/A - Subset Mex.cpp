#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int a[maxN], cnt[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      cnt[a[i]]++;
    }

    int ans = 0;
    for (int i = 0; i <= maxN; i++)
    {
      while (cnt[i] >= 2) i++;
      if (cnt[i] == 0) ans += 2*i;
      else
      {
        ans += i;
        while (cnt[i] >= 1) i++;
        ans += i;
      }
      break;
    }
    printf("%d\n", ans);
  }
  return 0;
}
