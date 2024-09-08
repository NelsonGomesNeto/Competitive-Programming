#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
map<int, int> cnt[2];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    cnt[0].clear(), cnt[1].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
      if (!cnt[1].count(a[i]))
        cnt[1][a[i]] = 0;
      cnt[1][a[i]]++;
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++)
    {
      if (!cnt[0].count(a[i]))
        cnt[0][a[i]] = 0;
      cnt[0][a[i]]++;
      if (--cnt[1][a[i]] == 0)
        cnt[1].erase(a[i]);

      if (cnt[0].size() == i + 1 && cnt[0].rbegin()->first == i
        && cnt[1].size() == n - (i + 1) && cnt[1].rbegin()->first == n - (i + 1) - 1)
        ans.push_back({i + 1, n - (i + 1)});
    }
    printf("%d\n", (int)ans.size());
    for (auto &p: ans) printf("%d %d\n", p.first, p.second);
  }
  return 0;
}
