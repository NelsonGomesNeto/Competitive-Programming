#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
int a[maxN], b[maxN], c[maxN];
deque<int> missingByColor[maxN + 1];
set<int> colorPos[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; i++)
      colorPos[i].clear(), missingByColor[i].clear();

    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &b[i]);
      colorPos[b[i]].insert(i);
    }
    for (int i = 0; i < m; i++)
      scanf("%d", &c[i]);

    for (int i = 0; i < n; i++)
      if (a[i] != b[i])
        missingByColor[b[i]].push_back(i);

    int aux = -1;
    for (int i = 0; i < n; i++)
      if (a[i] == b[i] && c[m - 1] == b[i])
        aux = i;
    for (int i = 0; i < n; i++)
      if (a[i] != b[i] && c[m - 1] == b[i])
        aux = i;

    vector<int> ans;
    for (int i = 0; i < m; i++)
    {
      int idx;
      if (!missingByColor[c[i]].empty())
      {
        idx = missingByColor[c[i]].front();
        missingByColor[c[i]].pop_front();
      }
      else if (aux != -1)
        idx = aux;
      else if (!colorPos[c[i]].empty())
        idx = *colorPos[c[i]].begin();
      else
        break;

      ans.push_back(idx);
      colorPos[a[idx]].erase(idx);
      a[idx] = c[i];
      colorPos[c[i]].insert(idx);
    }

    bool valid = true;
    for (int i = 0; i < n; i++)
      if (a[i] != b[i])
        valid = false;

    if (ans.size() == m && valid)
    {
      printf("YES\n");
      for (int i = 0; i < m; i++)
        printf("%d%c", ans[i] + 1, i < m - 1 ? ' ' : '\n');
    }
    else
      printf("NO\n");
  }
  return 0;
}
