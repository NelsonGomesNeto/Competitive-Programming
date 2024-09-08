#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
pair<int, int> p[maxN];
int cnt[maxN];
map<int, set<int>> mx;
set<int> pos;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    pos.clear(); mx.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i].first);
      p[i].second = i;
      cnt[i] = 1;
      mx[1].insert(i);
      pos.insert(i);
    }
    sort(p, p+n);

    bool can = true;
    for (int i = 0; i < n; i++)
    {
      if (!mx.rbegin()->second.count(p[i].second))
      {
        can = false;
        break;
      }
      pos.erase(p[i].second);
      mx.rbegin()->second.erase(p[i].second);

      if (mx.rbegin()->second.empty())
        mx.erase(prev(mx.end()));

      if (pos.lower_bound(p[i].second) != pos.end())
      {
        DEBUG printf("%d %d %d\n", p[i].first, p[i].second, *pos.lower_bound(p[i].second));
        mx[mx.rbegin()->first + 1].insert(*pos.lower_bound(p[i].second));
      }
    }
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
