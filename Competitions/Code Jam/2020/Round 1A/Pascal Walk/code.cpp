#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1
1 1
1 2 1
1 3 3 1
*/

const int maxN = 500; lli n;
lli pascal[maxN][maxN];

int di[6] = {-1, -1, 0, 0, 1, 1}, dj[6] = {-1, 0, -1, 1, 0, 1};

struct Node
{
  lli value;
  vector<pair<int, int>> path;
  bool operator<(const Node &other) const { return value < other.value || (value == other.value && path.size() > other.path.size()); }
};
vector<pair<int, int>> solve()
{
  priority_queue<Node> pq;
  pq.push({1, {{0, 0}}});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    if (u.value == n) return u.path;
    if (u.path.size() == maxN) continue;
    for (int k = 3; k < 6; k++)
    {
      int i = u.path.back().first + di[k], j = u.path.back().second + dj[k];
      if (u.value + pascal[i][j] <= n)
      {
        u.path.push_back({i, j});
        pq.push({u.value + pascal[i][j], u.path});
        u.path.pop_back();
      }
    }
  }
  vector<pair<int, int>> a;
  return a;
}

int main()
{
  pascal[0][0] = 1;
  for (int i = 1; i < maxN; i++)
    for (int j = 0; j <= i; j++)
      pascal[i][j] = pascal[i - 1][j] + (j ? pascal[i - 1][j - 1] : 0);

  DEBUG {
    for (int i = 0; i < 100; i++)
      for (int j = 0; j <= i; j++)
        printf("%lld%c", pascal[i][j], j < i ? ' ' : '\n');
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &n);
    vector<pair<int, int>> ans = solve();
    printf("Case #%d:\n", tt);
    for (auto &p: ans)
      printf("%d %d\n", p.first + 1, p.second + 1);
  }


  return 0;
}