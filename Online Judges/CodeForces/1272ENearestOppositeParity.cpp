#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, inf = 1e7; int n;
int a[maxN];

vector<int> in[maxN];
vector<vector<int>> atDist;
int ans[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(ans, -1, sizeof(ans));
    atDist.clear();
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    atDist.push_back(vector<int>());
    for (int i = 0; i < n; i ++)
      for (int j = -1; j <= 1; j += 2)
      {
        int ni = i + j*a[i];
        if (ni < 0 || ni >= n) continue;
        in[ni].push_back(i);
        if ((a[ni] & 1) != (a[i] & 1))
          ans[i] = 1, atDist[0].push_back(i);
      }

    for (int i = 0; i < atDist.size(); i ++)
    {
      for (int j = 0; j < atDist[i].size(); j ++)
      {
        int u = atDist[i][j];
        DEBUG printf("\tTrying dist %d with %d - %d\n", i + 1, u, a[u]);
        for (int v: in[u])
        {
          DEBUG printf("\t\t%d | %d | %d\n", v, a[v], ans[v]);
          if (ans[v] == -1 && (a[u] & 1) == (a[v] & 1))
          {
            ans[v] = i + 2;
            if (i + 2 > atDist.size()) atDist.push_back(vector<int>());
            atDist[i + 1].push_back(v);
          }
        }
      }
    }

    for (int i = 0; i < n; i ++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
