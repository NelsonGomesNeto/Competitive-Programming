#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
char graph[maxN][maxN + 1];

/*
  If there's u <-> v where both edges have the same letter: done
*/
vector<int> ans;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf(" %s", graph[i]);

    ans.clear();
    bool can = false;
    for (int u = 0; u < n && !can; u++)
      for (int v = u + 1; v < n && !can; v++)
        if (graph[u][v] == graph[v][u])
        {
          can = true;
          for (int i = 0; i <= m; i++)
            ans.push_back(i & 1 ? v : u);
        }

    if (!can)
    {
      if (m & 1)
      {
        can = true;
        for (int i = 0; i <= m; i++)
          ans.push_back(i & 1 ? 0 : 1);
      }
      else if (n > 2)
      {
        can = true;
        vector<int> xyz = {0, 1, 2};
        int x, y, z;
        do
        {
          x = xyz[0], y = xyz[1], z = xyz[2];
          if (graph[x][y] == graph[y][z] && graph[z][y] == graph[y][x])
            break;
        }
        while (next_permutation(xyz.begin(), xyz.end()));

        for (int i = 0, mid = m >> 1; i <= mid; i++)
          ans.push_back(i & 1 ? x : y);
        reverse(ans.begin(), ans.end());
        for (int i = 0, mid = m >> 1; i < mid; i++)
          ans.push_back(i & 1 ? y : z);
      }
    }

    DEBUG {
      string s = "";
      for (int i = 1; i < ans.size(); i++)
        s += graph[ans[i - 1]][ans[i]];
      printf("\t%s\n", s.c_str());
    }

    if (can)
    {
      printf("YES\n");
      for (int i = 0; i < ans.size(); i++)
        printf("%d%c", ans[i] + 1, i < ans.size() - 1 ? ' ' : '\n');
    }
    else
      printf("NO\n");
  }
  return 0;
}
