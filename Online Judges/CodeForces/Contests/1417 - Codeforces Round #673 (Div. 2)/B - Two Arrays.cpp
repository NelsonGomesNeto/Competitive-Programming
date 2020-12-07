#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli bad;
lli a[maxN];
map<lli, vector<int>> pos;
set<lli> done;

bool p[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %lld", &n, &bad);
      pos.clear();
      for (int i = 0; i < n; i++)
      {
        scanf("%lld", &a[i]);
        pos[a[i]].push_back(i);
      }

      done.clear();
      for (int i = 0; i < n; i++) p[i] = false;
      for (auto &hehe: pos)
      {
        if (!done.count(hehe.first) && 2LL*hehe.first != bad && pos.count(bad - hehe.first)
          && !pos[bad - hehe.first].empty())
        {
          for (int j = 0; j < hehe.second.size(); j++)
            p[hehe.second[j]] = true;
          done.insert(bad - hehe.first);
        }
        done.insert(hehe.first);
      }

      if (!(bad & 1) && pos.count(bad >> 1LL) && !pos[bad >> 1LL].empty())
      {
        int toRight = pos[bad >> 1LL].size() >> 1;
        for (int i = 0; i < toRight; i++)
          p[pos[bad >> 1LL][i]] = true;
      }

      for (int i = 0; i < n; i++)
        printf("%d%c", p[i], i < n - 1 ? ' ' : '\n');
    }
  return 0;
}
