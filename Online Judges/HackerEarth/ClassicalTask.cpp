#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  The idea is to use DSU and logarithm decomposition (the same LCA's binary lifting idea)
  First of all, duplicate the array [1:n], such that you will have this:
  positions: 1 | 2 | ... | n | (n + 1) | ... | (2n - 1) | 2n
  meaning  : 1 | 2 | ... | n | (n - 1) | ... |        2 |  1
  This way you can use only addings to fill the edges of a query:
    originally: (L, R) -> (L, R), (L + 1, R - 1), ..., (R, L)
    now: (L, R) -> (L, 2n - R + 1), (L + 1, 2n - R + 2), ..., (R, 2n - R + 1 + (R - L))
      Notice how adding on the right side still means a descrease in the indexes
      Yes, these aren't the original vertices/edges, but in the end, if you for every i
      merge i with 2n - i + 1, you will end up with the same amount of components, since
      they are just two representations of the same vertex
  Now, query(L, R) can be represented as: query(L, 2n - R + 1, k), where k is R - L + 1, which means
  that you will have the edges: (L, 2n - R + 1), (L + 1, 2n - R + 2), ... (R, 2n - R + k)
  Make a vector<pair<int, int>> for each power of two (there will be at most 20)
  For each query:
    Decompose k into its powers of two (Example: 5 is 2^2 + 2^0), and for each power of two:
      query[power of two].add(L, 2n - R + 1)
      L = L + this power of two
      2n - R + 1 = 2n - R + 1 + this power of two
  For p in powers of two (from 20 to 0):
    reset the DSU
    for q in query[p]: merge(q.first, q.second)
    if p == 0: break
    for i in (1 to 2n):
      if (i isn't root):
        query[p - 1].add(i, root(i))
        query[p - 1].add(i + (1 << (p - 1)), root(i) + (1 << (p - 1)))
        (You will be breaking the 2^k to two, until you reach 2^0)
        (This will only send further down this component by making every one merge with it's known root)
    (Can you see how you will add at most 2*2*n queries to the next power of two?)
  For every i in (1 to n): merge(i, 2n - i + 1)
  print(countComponents())
*/

const int maxN = 5e5, maxM = 1e5, maxLog = 20; int n, m;
int logdp[maxN + 1];
vector<pair<int, int>> edges[maxLog];

int parent[2*maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}

int main()
{
  for (int i = 2, end = maxN; i <= end; i ++) logdp[i] = logdp[i >> 1] + 1;

  scanf("%d %d", &n, &m);

  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    int revV = 2*n - v - 1, dist = v - u + 1;
    for (int j = logdp[dist]; j > 0; j --)
      if ((1 << j) & dist)
      {
        edges[j].push_back({u, revV});
        u += 1 << j, revV += 1 << j;
      }
  }

  for (int j = logdp[n]; j >= 0; j --)
  {
    memset(parent, -1, sizeof(parent));
    for (auto &i: edges[j])
      merge(i.first, i.second);
    if (j == 0) break;

    for (int i = 0, end = 2*n, mid = 1 << (j - 1); i < end; i ++)
      if (parent[i] >= 0) // isn't root
        edges[j - 1].push_back({i, root(i)}), edges[j - 1].push_back({i + mid, root(i) + mid});
    edges[j].clear();
  }

  for (int i = 0; i < n; i ++)
    merge(i, 2*n - i - 1);

  int components = 0;
  for (int i = 0, end = 2*n; i < end; i ++)
    components += parent[i] < 0; // is root
  printf("%d\n", components);

  return(0);
}