#include <bits/stdc++.h>
using namespace std;
const int maxN = 5e4;
vector<int> tree[maxN], cardToPos[maxN >> 1];
int n, posToCard[maxN], level[maxN];
int now, first[maxN], uMap[maxN], revMap[maxN], sparseTable[2*maxN][(int) floor(log2(2*maxN)) + 1], logDP[2*maxN + 1];
vector<int> eulerianTour;

void printSpacing(int depth) { while (depth --) printf("   "); }

void dfs(int u, int prev, int depth)
{
  // printSpacing(depth); printf("(%d, %d)\n", posToCard[u], u);
  revMap[now] = u; uMap[u] = now ++; level[u] = depth;
  first[u] = eulerianTour.size();
  eulerianTour.push_back(uMap[u]);
  for (auto v: tree[u])
    if (v != prev)
    {
      dfs(v, u, depth + 1);
      eulerianTour.push_back(uMap[u]);
    }
}

void build()
{
  logDP[1] = 0; for (int i = 2; i <= 2*maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  now = 0; dfs(0, -1, 0); int logn = floor(log2(eulerianTour.size())) + 1;
  for (int i = 0; i < eulerianTour.size(); i ++) sparseTable[i][0] = eulerianTour[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i + shift < eulerianTour.size(); i ++)
      sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + shift][j - 1]);
}

int LCA(int u, int v)
{
  int lo = min(first[u], first[v]), hi = max(first[u], first[v]);
  int qs = logDP[hi - lo + 1];
  return(revMap[min(sparseTable[lo][qs], sparseTable[hi - (1 << qs) + 1][qs])]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0, a; i < n; i ++)
  {
    scanf("%d", &a); a --;
    cardToPos[a].push_back(i);
    posToCard[i] = a;
  }

  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  build();

  int score = 0, nn = n >> 1;
  for (int i = 0; i < nn; i ++)
  {
    // printf("%d %d %d %d - LCA: %d %d\n", cardToPos[i][0], cardToPos[i][1], level[cardToPos[i][0]], level[cardToPos[i][1]], LCA(uMap[cardToPos[i][0]], uMap[cardToPos[i][1]]), level[LCA(uMap[cardToPos[i][0]], uMap[cardToPos[i][1]])]);
    score += level[cardToPos[i][0]] + level[cardToPos[i][1]] - 2*level[LCA(cardToPos[i][0], cardToPos[i][1])];
  }
  printf("%d\n", score);
  return(0);
}
