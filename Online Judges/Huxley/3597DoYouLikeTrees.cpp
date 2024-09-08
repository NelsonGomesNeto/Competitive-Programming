#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
using namespace std;

const int maxN = 1e5;

struct TestCase
{
  int n;
  vector<vector<int>> tree;
  vector<lli> distanceSum;
  vector<int> subtreeSize;

  int buildSubtreeSize(int u = 0, int prv = -1)
  {
    subtreeSize[u] = 1;
    for (const int v : tree[u])
      if (v != prv)
        subtreeSize[u] += buildSubtreeSize(v, u);
    return subtreeSize[u];
  }
  lli solveRoot(int u = 0, int prv = -1, int d = 0)
  {
    lli ans = d;
    for (const int v : tree[u])
      if (v != prv)
        ans += solveRoot(v, u, d + 1);
    return ans;
  }
  void reRoot(lli currentSum, int u, int prv = -1)
  {
    distanceSum[u] = currentSum;
    for (const int v : tree[u])
      if (v != prv)
      {
        lli newSum =
            currentSum - subtreeSize[v] + (subtreeSize[0] - subtreeSize[v]);
        reRoot(newSum, v, u);
      }
  }
  tuple<int, int, int> mostDistant(int start)
  {
    queue<tuple<int, int, int>> q;
    q.push({start, 0, -1});
    int target, biggestDistance = 0, cnt;
    while (!q.empty())
    {
      auto [u, d, prv] = q.front();
      q.pop();
      if (d > biggestDistance)
      {
        biggestDistance = d, cnt = 1;
        target = u;
      }
      else if (d == biggestDistance)
      {
        ++cnt;
      }

      for (int v : tree[u])
        if (v != prv)
        {
          q.push({v, d + 1, u});
        }
    }
    return {target, biggestDistance, cnt};
  }
  lli diameterSum()
  {
    auto [u, d1, cnt1] = mostDistant(0);
    auto [v, diameter, cnt2] = mostDistant(u);
    auto [w, d3, cnt3] = mostDistant(v);
    DEBUG printf("\t%d %d | %d %d %d %d\n", u + 1, v + 1, diameter, cnt1, cnt2, cnt3);
    return (lli)cnt3 * cnt2 * diameter * 2;
  }

  void solve()
  {
    scanf("%d", &n);
    tree.resize(n);
    distanceSum.resize(n, 0);
    subtreeSize.resize(n, 0);

    for (int i = 1; i < n; ++i)
    {
      int u, v;
      scanf("%d %d", &u, &v);
      --u, --v;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }

    lli ans = 0;
    distanceSum[0] = solveRoot(0);
    buildSubtreeSize();
    reRoot(distanceSum[0], 0);
    for (int i = 0; i < n; ++i)
    {
      ans += distanceSum[i];
      DEBUG printf("\tdistanceSum[%d] = %lld\n", i + 1, distanceSum[i]);
    }
    ans -= diameterSum();
    ans >>= 1;
    printf("%lld\n", ans);
  }
};
TestCase test_case;

int main()
{
  test_case = TestCase{};
  test_case.solve();
  return 0;
}
