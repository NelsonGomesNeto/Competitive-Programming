#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n, m;
int mat[maxN][maxN];

int segtree2d[4*maxN][4*maxN], null = 0;
inline int f(int a, int b) { return(a + b); }
void buildHorizontal(int i, int loi, int hii, int j = 1, int loj = 0, int hij = m - 1)
{
  if (loj == hij)
  {
    if (loi == hii)
      segtree2d[i][j] = mat[loi][loj];
    else
      segtree2d[i][j] = f(segtree2d[2*i][j], segtree2d[2*i + 1][j]);
    return;
  }
  int midj = (loj + hij) >> 1;
  buildHorizontal(i, loi, hii, 2*j, loj, midj), buildHorizontal(i, loi, hii, 2*j + 1, midj + 1, hij);
  segtree2d[i][j] = f(segtree2d[i][2*j], segtree2d[i][2*j + 1]);
}
void build(int i = 1, int loi = 0, int hii = n - 1)
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
int queryHorizontal(int qloi, int qloj, int qhii, int qhij, int i, int j = 1, int loj = 0, int hij = m - 1)
{
  if (hij < qloj || loj > qhij) return(null);
  if (loj >= qloj && hij <= qhij) return(segtree2d[i][j]);
  int midj = (loj + hij) >> 1;
  return(f(queryHorizontal(qloi, qloj, qhii, qhij, i, 2*j, loj, midj), queryHorizontal(qloi, qloj, qhii, qhij, i, 2*j + 1, midj + 1, hij)));
}
int query(int qloi, int qloj, int qhii, int qhij, int i = 1, int loi = 0, int hii = n - 1)
{
  if (hii < qloi || loi > qhii) return(null);
  if (loi >= qloi && hii <= qhii) return(queryHorizontal(qloi, qloj, qhii, qhij, i));
  int midi = (loi + hii) >> 1;
  return(f(query(qloi, qloj, qhii, qhij, 2*i, loi, midi), query(qloi, qloj, qhii, qhij, 2*i + 1, midi + 1, hii)));
}
void updateHorizontal(int ui, int uj, int value, int i, int loi, int hii, int j = 1, int loj = 0, int hij = m - 1)
{
  if (loj == hij)
  {
    if (loi == hii)
      segtree2d[i][j] = mat[loi][loj] = value;
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
void update(int ui, int uj, int value, int i = 1, int loi = 0, int hii = n - 1)
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

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  build();

  printf("%*c |", 5, ' '); for (int i = 0; i < 4*m; i ++) printf("%5d%c", i, i < 4*m - 1 ? ' ' : '\n');
  for (int i = 0; i < 4*n; i ++)
  {
    printf("%5d |", i);
    for (int j = 0; j < 4*m; j ++)
      printf("%5d%c", segtree2d[i][j], j < 4*m - 1 ? ' ' : '\n');
  }

  int q; scanf("%d", &q);
  while (q --)
  {
    int op; scanf("%d", &op);
    if (op == 2)
    {
      int loi, loj, hii, hij; scanf("%d %d %d %d", &loi, &loj, &hii, &hij);
      printf("%d\n", query(loi, loj, hii, hij));
    }
    else
    {
      int i, j, value; scanf("%d %d %d", &i, &j, &value);
      update(i, j, value);
    }
  }

  return(0);
}