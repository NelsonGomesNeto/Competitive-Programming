#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
const lli inf = 1e16;
int a[maxN];

struct SubArray
{
  lli sum; int size;
  SubArray operator+(const SubArray &sub) { return(SubArray({sum + sub.sum, size + sub.size})); }
  bool operator<(const SubArray &sub) const { return(sum < sub.sum || (sum == sub.sum && size < sub.size)); }
  void print()
  {
    printf("%lld %d\n", sum, size);
  }
};
struct Node
{
  SubArray total, best, left, right;
  // lli totalSum, bestSum, leftSum, rightSum; int totalSize, bestSize, leftSize, rightSize;
  Node operator+(const Node &node)
  {
    return(Node({total + node.total, max({best, node.best, right + node.left}), max(left, total + node.left), max(node.right, right + node.total)}));
  }
  void print()
  {
    best.print();
  }
};

Node segtree[4*maxN], nullNode = {{-inf, 0}, {-inf, 0}, {-inf, 0}, {-inf, 0}};
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = Node({{a[lo], 1}, {a[lo], 1}, {a[lo], 1}, {a[lo], 1}});
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
  DEBUG {
    printf("[%d, %d] = ", lo, hi);
    segtree[i].print();
  }
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > qhi || hi < qlo) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int pos, lli value, int i = 1, int lo = 0, int hi = n - 1);

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    
    build();

    int q; scanf("%d", &q);
    while (q --)
    {
      int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
      query(lo, hi).print();
    }
  }
  return(0);
}