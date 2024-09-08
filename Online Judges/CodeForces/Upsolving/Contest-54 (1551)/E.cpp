#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, k;
int a[maxN];

int memo[maxN][maxN + 1];
int solve(int i = 0, int idx = 1)
{
  if (i == n) return 0;
  int &ans = memo[i][idx];
  if (ans != -1) return ans;

  ans = 0;
  if (a[i] == idx) ans = max(ans, solve(i + 1, idx + 1) + 1);
  ans = max(ans, solve(i + 1, idx));
  ans = max(ans, solve(i + 1, idx + 1));

  return ans;
}
unordered_map<short, short> memo2[maxN][maxN + 1];
struct Node
{
  int i, idx, good, d;
  bool operator<(const Node &other) const { return d > other.d || (d == other.d && good < other.good); }
};
short solve2()
{
  priority_queue<Node> pq;
  memo2[0][1][0] = 0;
  pq.push(Node{0, 1, 0, 0});

  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    if (u.good == k) return u.d;
    if (u.good + solve(u.i, u.idx) < k) continue;
    if (u.i == n) continue;

    if (memo2[u.i][u.idx].count(u.good) && memo2[u.i][u.idx][u.good] < u.d) continue;

    if (a[u.i] == u.idx)
    {
      if (!memo2[u.i + 1][u.idx + 1].count(u.good + 1) || u.d < memo2[u.i + 1][u.idx + 1][u.good + 1])
      {
        memo2[u.i + 1][u.idx + 1][u.good + 1] = u.d;
        pq.push(Node{u.i + 1, u.idx + 1, u.good + 1, u.d});
      }
    }
    if (!memo2[u.i + 1][u.idx].count(u.good) || u.d + 1 < memo2[u.i + 1][u.idx][u.good])
    {
      memo2[u.i + 1][u.idx][u.good] = u.d + 1;
      pq.push(Node{u.i + 1, u.idx, u.good, u.d + 1});
    }
    if (!memo2[u.i + 1][u.idx + 1].count(u.good) || u.d < memo2[u.i + 1][u.idx + 1][u.good])
    {
      memo2[u.i + 1][u.idx + 1][u.good] = u.d;
      pq.push(Node{u.i + 1, u.idx + 1, u.good, u.d});
    }
  }

  return 32000;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= n; j++)
        memo2[i][j].clear();
    int ans = solve() >= k ? solve2() : 32000;
    if (ans >= 32000) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}
