#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
char s[maxN];

struct Node
{
  int cnt[26];
  Node operator+(const Node &other)
  {
    Node ans;
    for (int i = 0; i < 26; i ++)
      ans.cnt[i] = cnt[i] + other.cnt[i];
    return ans;
  }
  void print()
  {
    int ans = 0;
    for (int i = 0; i < 26; i ++)
      ans += cnt[i] > 0;
    printf("%d\n", ans);
  }
};
Node segtree[4*maxN], nullNode;
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i].cnt[s[lo] - 'a'] ++;
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return nullNode;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int pos, char value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i].cnt[s[lo] - 'a'] --;
    segtree[i].cnt[(s[lo] = value) - 'a'] ++;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  scanf("%s", s); n = strlen(s);
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    int op; scanf("%d", &op);
    if (op == 1)
    {
      int pos; char value; scanf("%d %c", &pos, &value); pos --;
      update(pos, value);
    }
    else
    {
      int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
      query(lo, hi).print();
    }
  }
  return 0;
}
