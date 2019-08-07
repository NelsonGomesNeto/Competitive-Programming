#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, k;
int a[maxN];

struct Node
{
  int negatives, zeros;
  Node operator+(const Node &node)
  {
    return(Node({negatives + node.negatives, zeros + node.zeros}));
  }
  void print()
  {
    printf("%c", zeros ? '0' : negatives & 1 ? '-' : '+');
  }
};
Node segtree[4*maxN], nullNode = {0, 0};
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = {a[lo] < 0, a[lo] == 0};
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = {value < 0, value == 0};
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);
    build();
    while (k --)
    {
      char op; scanf(" %c", &op);
      if (op == 'P')
      {
        int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
        query(lo, hi).print();
      }
      else
      {
        int pos, value; scanf("%d %d", &pos, &value); pos --;
        update(pos, value);
      }
    }
    printf("\n");
  }
  return(0);
}