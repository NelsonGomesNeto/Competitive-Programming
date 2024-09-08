#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, m;
int s[maxN];
vector<int> p[maxN];
map<int, int> cnt[maxN];

map<int, int> cc;
map<int, int> possible;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) scanf("%d", &s[i]);

    cc.clear();
    for (int i = 0; i < n; i++)
    {
      p[i].clear();
      p[i].resize(m);
      cnt[i].clear();
      for (auto &pp: p[i])
      {
        scanf("%d", &pp);
        cnt[i][pp]++;
      }
      // sort(p[i].begin(), p[i].end());
    }
    DEBUG
    for (int i = 0; i < n; i++)
    {
      printf("\t");
      for (auto &pp: p[i]) printf("%2d ", pp);
      printf("\n");
    }

    int ans = 0;
    list<int> curr;
    for (int j = 0; j < m; j++) curr.push_back(j);
    list<int> nxt;

    for (int i = 0; i < n; i++)
    {
      nxt.clear();
      for (int j: curr)
        if (cnt[i].count(s[j]))
        {
          nxt.push_back(j);
          if (--cnt[i][s[j]])
            cnt[i].erase(s[j]);
        }
      ans += max(0, m - (int)nxt.size());
      curr = nxt;
    }
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}