#include <bits/stdc++.h>
using namespace std;

const int maxN = 52, inf = 1e6; int n, m;
int mat[maxN][maxN];
int di[4] = {1, 0, -1, 0}, dj[4] = {0, 1, 0, -1};
set<set<pair<int, int>>> forms;

set<pair<int, int>> normalize(set<pair<int, int>> &a)
{
  set<pair<int, int>> aa;
  int i = a.begin()->first, j = a.begin()->second;
  for (auto &p: a) aa.insert({p.first - i, p.second - j});
  return(aa);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < maxN; i ++) for (int j = 0; j < maxN; j ++) mat[i][j] = -inf;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      scanf("%d", &mat[i][j]);

  set<pair<int, int>> lol; lol.insert({0, 0});
  forms.insert(lol);
  for (int pp = 2; pp <= m; pp ++)
    for (auto each: forms)
    {
      if (each.size() == pp) continue;
      if (each.size() < pp - 1) { forms.erase(each); continue; }
      for (int k = 0; k < 4; k ++)
        for (auto &p: each)
        {
          set<pair<int, int>> a = each;
          int i = p.first + di[k], j = p.second + dj[k];
          a.insert({i, j});
          if (a.size() < pp) continue;
          a = normalize(a);
          forms.insert(a);
        }
    }
  // printf("%d\n", (int) forms.size());
  vector<vector<pair<int, int>>> fastForms;
  for (auto &each: forms)
  {
    vector<pair<int, int>> lol;
    for (auto &p: each) lol.push_back(p);
    fastForms.push_back(lol);
  }

  int ans = -inf;
  for (auto &each: fastForms)
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= n; j ++)
      {
        int s = 0;
        for (auto &p: each)
        {
          s += mat[i + p.first][j + p.second];
          if (s < 0) break;
        }
        ans = max(ans, s);
      }
  printf("%d\n", ans);

  return(0);
}