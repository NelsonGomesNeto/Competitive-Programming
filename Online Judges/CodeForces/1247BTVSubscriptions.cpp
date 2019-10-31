#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k, d;
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d %d", &n, &k, &d);
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);
    map<int, int> cnt;
    for (int i = 0; i < d; i ++)
    {
      if (!cnt.count(a[i]))
        cnt[a[i]] = 0;
      cnt[a[i]] ++;
    }
    int ans = cnt.size();
    for (int i = d; i < n; i ++)
    {
      if (-- cnt[a[i - d]] == 0)
        cnt.erase(a[i - d]);
      if (!cnt.count(a[i]))
        cnt[a[i]] = 0;
      cnt[a[i]] ++;
      ans = min(ans, (int) cnt.size());
    }
    printf("%d\n", ans);
  }
  return 0;
}
