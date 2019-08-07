#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxR = 500, maxN = 5, inf = 1e9; int r, c, n;
int rentingCost[maxR][maxR], rowRange[maxR][maxR], columnRange[maxR][maxR];
struct Pos
{
  int i, j;
  bool operator<(const Pos &p) const { return(i < p.i || (i == p.i && j < p.j)); }
  bool operator==(const Pos &p) const { return(i == p.i && j == p.j); }
};
Pos path[maxN]; int dist[maxR][maxR], notVisited[maxR][maxR], ans[maxN - 1]; float euclidDist[maxR][maxR];

void read(int mat[maxR][maxR])
{
  for (int i = 0; i < r; i ++)
    for (int j = 0; j < c; j ++)
      scanf("%d", &mat[i][j]);
}

int segtree2d[4*maxR][4*maxR], null = 0;
inline int f(int a, int b) { return(a + b); }
void buildHorizontal(int i, int loi, int hii, int j = 1, int loj = 0, int hij = c - 1)
{
  if (loj == hij)
  {
    if (loi == hii)
      segtree2d[i][j] = notVisited[loi][loj];
    else
      segtree2d[i][j] = f(segtree2d[2*i][j], segtree2d[2*i + 1][j]);
    return;
  }
  int midj = (loj + hij) >> 1;
  buildHorizontal(i, loi, hii, 2*j, loj, midj), buildHorizontal(i, loi, hii, 2*j + 1, midj + 1, hij);
  segtree2d[i][j] = f(segtree2d[i][2*j], segtree2d[i][2*j + 1]);
}
void build(int i = 1, int loi = 0, int hii = r - 1)
{
  if (loi == hii)
  {
    buildHorizontal(i, loi, hii);
    return;
  }
  int midi = (loi + hii) >> 1;
  build(2*i, loi, midi), build(2*i + 1, midi + 1, hii);
  buildHorizontal(i, loi, hii);
}
int queryHorizontal(int qloi, int qloj, int qhii, int qhij, int i, int j = 1, int loj = 0, int hij = c - 1)
{
  if (hij < qloj || loj > qhij) return(null);
  if (loj >= qloj && hij <= qhij) return(segtree2d[i][j]);
  int midj = (loj + hij) >> 1;
  return(f(queryHorizontal(qloi, qloj, qhii, qhij, i, 2*j, loj, midj), queryHorizontal(qloi, qloj, qhii, qhij, i, 2*j + 1, midj + 1, hij)));
}
int query(int qloi, int qloj, int qhii, int qhij, int i = 1, int loi = 0, int hii = r - 1)
{
  if (hii < qloi || loi > qhii) return(null);
  if (loi >= qloi && hii <= qhii) return(queryHorizontal(qloi, qloj, qhii, qhij, i));
  int midi = (loi + hii) >> 1;
  return(f(query(qloi, qloj, qhii, qhij, 2*i, loi, midi), query(qloi, qloj, qhii, qhij, 2*i + 1, midi + 1, hii)));
}
void updateHorizontal(int ui, int uj, int value, int i, int loi, int hii, int j = 1, int loj = 0, int hij = c - 1)
{
  if (loj == hij)
  {
    if (loi == hii)
      segtree2d[i][j] = notVisited[loi][loj] = value;
    else
      segtree2d[i][j] = f(segtree2d[2*i][j], segtree2d[2*i + 1][j]);
    return;
  }
  int midj = (loj + hij) >> 1;
  if (uj <= midj)
    updateHorizontal(ui, uj, value, i, loi, hii, 2*j, loj, midj);
  else
    updateHorizontal(ui, uj, value, i, loi, hii, 2*j + 1, midj + 1, hij);
  segtree2d[i][j] = f(segtree2d[i][2*j], segtree2d[i][2*j + 1]);
}
void update(int ui, int uj, int value, int i = 1, int loi = 0, int hii = r - 1)
{
  if (loi == hii)
  {
    updateHorizontal(ui, uj, value, i, loi, hii);
    return;
  }
  int midi = (loi + hii) >> 1;
  if (ui <= midi)
    update(ui, uj, value, 2*i, loi, midi);
  else
    update(ui, uj, value, 2*i + 1, midi + 1, hii);
  updateHorizontal(ui, uj, value, i, loi, hii);
}

priority_queue<pair<pair<int, float>, Pos>> pq;
void pushBlock(int loi, int loj, int hii, int hij, int prvD)
{
  if (loi > hii || loj > hij || !query(loi, loj, hii, hij)) return;
  if (loi == hii && loj == hij)
  {
    update(loi, loj, 0);
    pq.push({{-(dist[loi][loj] = prvD + rentingCost[loi][loj]), -euclidDist[loi][loj]}, {loi, loj}});
    return;
  }
  int midi = (loi + hii) >> 1, midj = (loj + hij) >> 1;
  pushBlock(loi, loj, midi, midj, prvD);
  pushBlock(loi, midj + 1, midi, hij, prvD);
  pushBlock(midi + 1, loj, hii, midj, prvD);
  pushBlock(midi + 1, midj + 1, hii, hij, prvD);
}
int dijkstra(Pos origin, Pos destination)
{
  while (!pq.empty()) pq.pop();
  for (int i = 0; i < r; i ++)
    for (int j = 0; j < c; j ++)
      dist[i][j] = inf, euclidDist[i][j] = sqrt((destination.i - i)*(destination.i - i) + (destination.j - j)*(destination.j - j)), notVisited[i][j] = 1;
  notVisited[origin.i][origin.j] = 0;
  build();
  pq.push({{-(dist[origin.i][origin.j] = rentingCost[origin.i][origin.j]), 0}, origin});
  while (!pq.empty())
  {
    Pos u = pq.top().second; int d = -pq.top().first.first; pq.pop();
    if (u == destination) return(dist[destination.i][destination.j] - rentingCost[destination.i][destination.j]);
    if (d > dist[u.i][u.j]) continue;
    pushBlock(max(0, u.i - rowRange[u.i][u.j]), max(0, u.j - columnRange[u.i][u.j]),
              min(r - 1, u.i + rowRange[u.i][u.j]), min(c - 1, u.j + columnRange[u.i][u.j]),
              dist[u.i][u.j]);
  }
  return(-1);
}

int main()
{
  scanf("%d %d %d", &r, &c, &n);
  read(rentingCost); read(rowRange); read(columnRange);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &path[i].i, &path[i].j);
    path[i].i --, path[i].j --;
  }

  for (int i = 1; i < n; i ++)
    ans[i - 1] = dijkstra(path[i - 1], path[i]);
  for (int i = 0; i < n - 1; i ++)
    printf("%d%c", ans[i], i < n - 2 ? ' ' : '\n');

  return(0);
}