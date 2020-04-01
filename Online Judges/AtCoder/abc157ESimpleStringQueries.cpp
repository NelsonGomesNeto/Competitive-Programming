#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n;
char s[maxN + 1];

int segtree[26][4*maxN];
void build(int k, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[k][i] = (s[lo] - 'a') == k;
    return;
  }
  int mid = (lo + hi) >> 1;
  build(k, 2*i, lo, mid), build(k, 2*i + 1, mid + 1, hi);
  segtree[k][i] = segtree[k][2*i] + segtree[k][2*i + 1];
}
int query(int k, int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[k][i];
  int mid = (lo + hi) >> 1;
  return query(k, qlo, qhi, 2*i, lo, mid) + query(k, qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int k, int pos, int diff, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[k][i] += diff;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(k, pos, diff, 2*i, lo, mid);
  else update(k, pos, diff, 2*i + 1, mid + 1, hi);
  segtree[k][i] = segtree[k][2*i] + segtree[k][2*i + 1];
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", s);
    for (int i = 0; i < 26; i ++)
      build(i);

    int q; scanf("%d", &q);
    while (q --)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int i; char c; scanf("%d %c", &i, &c); i --;
        if (s[i] != c)
        {
          update(s[i] - 'a', i, -1);
          update(c - 'a', i, 1);
          s[i] = c;
        }
      }
      else
      {
        int l, r; scanf("%d %d", &l, &r); l --, r --;
        int ans = 0;
        for (int i = 0; i < 26; i ++)
          ans += query(i, l, r) > 0;
        printf("%d\n", ans);
      }
    }
  }
  return 0;
}