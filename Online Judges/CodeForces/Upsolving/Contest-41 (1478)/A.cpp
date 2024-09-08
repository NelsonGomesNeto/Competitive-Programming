#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++)
    {
      int a; scanf("%d", &a);
      if (!cnt.count(a))
        cnt[a] = 0;
      cnt[a]++;
    }

    int ans = 0;
    while (!cnt.empty())
    {
      list<int> removed;
      for (auto &p: cnt)
      {
        if (--p.second == 0)
          removed.push_back(p.first);
      }
      for (int i: removed)
        cnt.erase(i);
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
