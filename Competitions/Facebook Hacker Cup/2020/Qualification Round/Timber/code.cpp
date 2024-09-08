#include <stdio.h>
#include <map>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  They will only combine when they share a position
  And standing trees will be ignored

  map<int, vector<int>>
  end position a tree will fell to -> list for starting positions
  (map since there may be multiple trees that can reach this position)

  Yes, you're right, but there's a problem:
  if the graph in a given position has too many edges, you'll always iterate over them
  (if you don't handle your states properly)

  So you must take advantage of the fact that there will be at most ONE tree in a given
  position
*/

const int maxN = 8e5; int n;
struct Tree
{
  int position, height;
  void read() { scanf("%d %d", &position, &height); }
  bool operator<(const Tree &other) const { return position < other.position; }
};
Tree trees[maxN];

struct Node
{
  int p, treeId, treePart; // 0 - base, 1 - left, 2 - right
  bool operator<(const Node &other) const { return p < other.p; }
};
unordered_map<int, vector<Node>> ugraph, dgraph;
void addEdge(int u, int v, int i, int treePart)
{
  if (u < v)
    ugraph[u].push_back({v, i, treePart});
  else
    dgraph[u].push_back({v, i, treePart});
  if (v < u)
    ugraph[v].push_back({u, i, 0});
  else
    dgraph[v].push_back({u, i, 0});
}

int memo[maxN][2][3];
// unordered_map<int, int> memo[2];
int dfs(int u, bool up, int i, int treePart)
{
  // if (memo[up].count(u)) return memo[up][u];
  if (memo[i][up][treePart] != -1) return memo[i][up][treePart];
  int ans = 0;
  if (up)
    for (auto &e: ugraph[u])
    {
      if (i != e.treeId)
        ans = max(ans, dfs(e.p, up, e.treeId, e.treePart) + (e.p - u));
    }
  else
    for (auto &e: dgraph[u])
    {
      if (i != e.treeId)
        ans = max(ans, dfs(e.p, up, e.treeId, e.treePart) + (u - e.p));
    }
  // return memo[up][u] = ans;
  return memo[i][up][treePart] = ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    ugraph.clear(), dgraph.clear();
    // memo[0].clear(), memo[1].clear();

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      trees[i].read();
      assert(trees[i].position >= -5e8 && trees[i].position <= 5e8);
      assert(trees[i].height >= 1 && trees[i].height <= 5e8);
      for (int j = 0; j < 2; j++)
        for (int k = 0; k < 3; k++)
          memo[i][j][k] = -1;
    }
    sort(trees, trees+n);
    reverse(trees, trees+n);

    if (tt == 42) continue;

    for (int i = 0; i < n; i++)
    {
      addEdge(trees[i].position, trees[i].position + trees[i].height, i, 2);
      addEdge(trees[i].position, trees[i].position - trees[i].height, i, 1);
    }

    for (auto &e: ugraph)
    {
      sort(e.second.begin(), e.second.end());
      reverse(e.second.begin(), e.second.end());
    }
    for (auto &e: dgraph)
    {
      sort(e.second.begin(), e.second.end());
      // reverse(e.second.begin(), e.second.end());
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      ans = max(
        {
          ans,
          dfs(trees[i].position + trees[i].height, true, i, 2) + trees[i].height,
          dfs(trees[i].position - trees[i].height, false, i, 1) + trees[i].height
        });
      DEBUG {
        if (i % 20 == 0) { printf("\n"); fflush(stdout); }
        printf("%d ", i);
      }
    }
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}
