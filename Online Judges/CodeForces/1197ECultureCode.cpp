#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  It's very important to notice that you can only insert a Matryoshka i inside
  a Matryoshka j iff:
    j.in >= i.out *and* the extraSpace left is the minimum possible

  There's only two cases:
    i doesn't fit in any Matryoshka: extraSpace = i.in, size = 1
    i fits in various Matryoshkas:
      But you can only insert in the ones with the minimum possible extraSpace
      Suppose that extraSpace is x, and there's y subsets of Matryoshkas with
      extraSpace == x
      So, by adding i: extraSpace = x - (i.out - i.in), size = y

  So, sort the Matryoshkas by in (descending)
  For each Matryoshka i:
    binarySearch for the first Matryoshka j where: j.in >= i.out
    if there's none:
      first case
      update position i to: extraSpace = i.in, size = 1
    else:
      query for x and y in the range: [j, n - 1]
      update position i to: extraSpace = x - (i.out - i.in), size = y
  Those queries and updates can be done using a segment tree
*/

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7, inf = 1e18;
struct Matryoshkas
{
  lli out, in;
  bool operator<(const Matryoshkas &mat) const
  {
    return(in < mat.in || (in == mat.in && out < mat.out));
  }
};
Matryoshkas mat[maxN];

struct Node
{
  lli extraSpace, size;
  Node operator+(const Node &node)
  {
    if (extraSpace < node.extraSpace) return(*this);
    else if (extraSpace > node.extraSpace) return(node);
    return(Node({extraSpace, (size + node.size) % mod}));
  }
  void print()
  {
    printf("%lld\n", size);
  }
};
Node segtree[4*maxN], nullNode = {inf, 0};
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int pos, Node value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%lld %lld", &mat[i].out, &mat[i].in);
  sort(mat, mat+n);

  for (int i = 0, end = 4*n; i < end; i ++)
    segtree[i] = nullNode;
  for (int i = n - 1; i >= 0; i --)
  {
    int pos = lower_bound(mat, mat+n, Matryoshkas({0, mat[i].out})) - mat;
    if (pos == n) // doesn't fit inside any bigger Matryoshka
    {
      update(i, Node({mat[i].in, 1}));
      continue;
    }
    Node minimum = query(pos, n - 1);
    update(i, Node({minimum.extraSpace - (mat[i].out - mat[i].in), minimum.size}));
  }

  query(0, n - 1).print();

  return(0);
}
