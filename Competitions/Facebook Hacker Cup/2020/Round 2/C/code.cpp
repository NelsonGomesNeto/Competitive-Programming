#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  There are 4 options for each event:
  1 - Wi > prvW and the edge is in the MST
    by removing this edge: we will certainly split the MST into two trees
    since every structure in this graph is a cycle, even the graph it self
    we will be either removing a sub-cycle edge, or a big cycle edge
    so we will need to check if in this sub-cycle/big cycle:
      there's a cheaper edge than Wi
      if so:
        remove the current Edge from the MST
        add the other Edge to the MST
      else:
        leave the graph as it its

  2 - Wi < prvW and the edge is in the MST
    Nothing changes

  3 - Wi > prvW and the edge isn't in the MST
    Nothing changes

  4 - Wi < prvW and the edge isn't in the MST
    Same as case 1
*/

const int maxN = 1e6 + 1; int n, m, e, k;
const lli maxCost = 1e9, mod = 1e9 + 7;
struct Edge
{
  int u, v; lli weight;
  int mstIdx;
};
vector<Edge> edges;
vector<set<pair<lli, int>>> msts; lli specials[maxN], sums[maxN];
lli contrib[maxN]; int other;

int x[maxN], y[maxN], edgeIdx[maxN]; lli newWeight[maxN];
lli ax, bx, cx;
lli ay, by, cy;
lli ai, bi, ci;
lli aw, bw, cw;

lli v[maxN];

void printEverything()
{
  DEBUG {
    printf("X: ");
    for (int i = 0; i < n; i++) printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
    printf("Y: ");
    for (int i = 0; i < n; i++) printf("%d%c", y[i], i < n - 1 ? ' ' : '\n');
    printf("I: ");
    for (int i = 0; i < e; i++) printf("%d%c", edgeIdx[i], i < e - 1 ? ' ' : '\n');
    printf("W: ");
    for (int i = 0; i < e; i++) printf("%lld%c", newWeight[i], i < e - 1 ? ' ' : '\n');
    printf("V: ");
    for (int i = 0; i < e; i++) printf("%lld%c", v[i], i < e - 1 ? ' ' : '\n');
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d %d", &n, &m, &e, &k);
    for (int i = 0; i < k; i++)
      scanf("%d", &x[i]);
    scanf("%lld %lld %lld", &ax, &bx, &cx);
    for (int i = k; i < n; i++)
      x[i] = (ax * x[i - 2] + bx * x[i - 1] + cx) % m;
    
    for (int i = 0; i < k; i++)
      scanf("%d", &y[i]);
    scanf("%lld %lld %lld", &ay, &by, &cy);
    for (int i = k; i < n; i++)
      y[i] = (ay * y[i - 2] + by * y[i - 1] + cy) % m;

    for (int i = 0; i < k; i++)
      scanf("%d", &edgeIdx[i]);
    scanf("%lld %lld %lld", &ai, &bi, &ci);
    for (int i = k; i < e; i++)
      edgeIdx[i] = (ai * edgeIdx[i - 2] + bi * edgeIdx[i - 1] + ci) % (n * m + n);
    
    for (int i = 0; i < k; i++)
      scanf("%lld", &newWeight[i]);
    scanf("%lld %lld %lld", &aw, &bw, &cw);
    for (int i = k; i < e; i++)
      newWeight[i] = (aw * newWeight[i - 2] + bw * newWeight[i - 1] + cw) % (maxCost);

    edges.clear(), msts.clear(), other = -1;
    for (int i = 0; i < n; i++)
    {
      msts.push_back(set<pair<lli, int>>());
      for (int j = 0; j < m; j++)
      {
        msts.back().insert({1, (int)edges.size()});
        edges.push_back(Edge{i*m + j, i*m + (j + 1) % m, 1, i});
      }
    }

    msts.push_back(set<pair<lli, int>>());
    for (int i = 0; i < n; i++)
    {
      msts.back().insert({1, (int)edges.size()});
      edges.push_back(Edge{i * m + y[i], ((i + 1) % n) * m + x[(i + 1) % n], 1, n});
    }

    v[0] = 0;
    for (int i = 0; i <= n; i++)
    {
      sums[i] = 0;
      for (auto &p: msts[i]) sums[i] += p.first;
      v[0] += contrib[i] = sums[i] - msts[i].rbegin()->first;
    }

    for (int i = 0; i < e; i++)
    {
      if (i) v[i] = v[i - 1];

      int mstIdx = edges[edgeIdx[i]].mstIdx;
      lli prvWeight = edges[edgeIdx[i]].weight;
      edges[edgeIdx[i]].weight = newWeight[i];

      lli delta = 0;

      if (mstIdx < n)
      {
        msts[mstIdx].erase({prvWeight, edgeIdx[i]});
        msts[mstIdx].insert({newWeight[i], edgeIdx[i]});
        vector<pair<lli, int>> secondOptions;
        for (auto it = prev(msts[mstIdx].end(), 3); it != msts[mstIdx].end(); it++)
          secondOptions.push_back(*it);
        reverse(secondOptions.begin(), secondOptions.end());

        pair<lli, int> a, b; bool canTwo = false;
        for (int j = 0; j < 3 && !canTwo; j++)
          for (int p = 1; p < 3 && !canTwo; p++)
          {
            int hehe[4] = {edges[secondOptions[j].second].u, edges[secondOptions[j].second].v,
                           edges[secondOptions[p].second].u, edges[secondOptions[p].second].v};
            map<int, int> cnt;
            bool can = true;
            for (int h = 0; h < 4; h++)
            {
              if (!cnt.count(hehe[h]))
                cnt[hehe[h]] = 0;
              if (++cnt[hehe[h]] == 2 && hehe[h] != x[mstIdx] && hehe[h] != y[mstIdx])
                can = false;
            }
            if (can)
              canTwo = true, a = secondOptions[j], b = secondOptions[p];
          }
        if (canTwo)
        {
          lli twoRemovalDelta = sums[mstIdx] - a.first - b.first;
          if (other == mstIdx)
            twoRemovalDelta
          else
            twoRemovalDelta += (sums[other] + a.) - contrib[other];
        }
      }
      else if (mstIdx < n)
      {
        // I can either remove one or two edges from this sub-cycle
        // But I can only remove two edges if they don't connect into the same
        // non x/y vertex
        msts[mstIdx].erase(msts[mstIdx].find(prvWeight));
        msts[mstIdx].insert(newWeight[i]);


      }
      else
      {

      }



      v[i] = (v[i] + delta + mod) % mod;
    }

    printEverything();

    lli ans = 1;
    for (int i = 0; i < e; i++)
      ans = (ans * v[i]) % mod;
    printf("Case #%d: %lld\n", tt, ans);

    DEBUG printf("\n");
  }
  return 0;
}