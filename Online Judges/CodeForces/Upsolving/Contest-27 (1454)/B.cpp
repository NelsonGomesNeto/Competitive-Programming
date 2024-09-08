#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> a;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    a.resize(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      if (!cnt.count(a[i]))
        cnt[a[i]] = 0;
      cnt[a[i]]++;
    }

    set<int> minimums;
    for (auto &i: cnt)
      if (i.second == 1)
        minimums.insert(i.first);

    int ans = -1, m = minimums.empty() ? -1 : *minimums.begin();
    for (int i = 0; i < n; i++)
      if (a[i] == m)
        ans = i + 1;
    printf("%d\n", ans);
  }
  return 0;
}
