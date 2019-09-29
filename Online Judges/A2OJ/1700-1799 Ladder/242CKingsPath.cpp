#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  It's very important to notice that the total length is 1e5
  So just map them all and do a BFS
*/

const int maxN = 1e5; int n, X0, Y0, X1, Y1;
set<pair<int, int>> valid; // (row, column)
map<pair<int, int>, int> dist;

int main()
{
  scanf("%d %d %d %d", &X0, &Y0, &X1, &Y1);
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int r, a, b; scanf("%d %d %d", &r, &a, &b);
    for (int j = a; j <= b; j ++)
      valid.insert({r, j});
  }

  queue<pair<int, int>> q; q.push({X0, Y0}); dist[{X0, Y0}] = 0;
  while (!q.empty())
  {
    pair<int, int> u = q.front(); q.pop();
    for (int di = -1; di <= 1; di ++)
      for (int dj = -1; dj <= 1; dj ++)
      {
        pair<int, int> v = {u.first + di, u.second + dj};
        if (valid.count(v) && !dist.count(v))
          q.push(v), dist[v] = dist[u] + 1;
      }
  }
  if (!dist.count({X1, Y1})) dist[{X1, Y1}] = -1;
  printf("%d\n", dist[{X1, Y1}]);

  return 0;
}