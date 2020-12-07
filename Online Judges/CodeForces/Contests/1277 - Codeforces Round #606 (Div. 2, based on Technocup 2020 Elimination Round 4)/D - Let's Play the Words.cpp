#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1];
vector<int> cnt[2][2];
vector<int> a[maxN];
set<vector<int>> all;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    all.clear();
    for (int i = 0; i < 2; i ++) for (int j = 0; j < 2; j ++) cnt[i][j].clear();

    int n; scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      a[i].clear();
      scanf(" %s", s);
      for (int j = 0; s[j]; j ++)
        a[i].push_back(s[j] - '0');
      all.insert(a[i]);
      cnt[a[i][0]][a[i].back()].push_back(i);
    }

    if (cnt[1][0].size() > cnt[0][1].size())
      swap(cnt[1][0], cnt[0][1]);

    if (cnt[0][1].empty() && !cnt[0][0].empty() && !cnt[1][1].empty())
    {
      printf("-1\n");
      continue;
    }

    vector<int> ans;
    if (cnt[0][1].size() >= cnt[1][0].size() + 2)
    {
      int todo = ((int) cnt[0][1].size() - (int) cnt[1][0].size()) >> 1;
      for (int p: cnt[0][1])
      {
        vector<int> aux = a[p];
        reverse(aux.begin(), aux.end());
        if (all.count(aux)) continue;
        ans.push_back(p), todo --;
        if (!todo) break;
      }
    }
    printf("%d\n", (int) ans.size());
    if (ans.empty()) printf("\n");
    for (int i = 0; i < ans.size(); i ++)
      printf("%d%c", ans[i] + 1, i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
