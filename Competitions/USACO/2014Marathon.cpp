#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)
using namespace std;

const int maxN = 1e5; int n, q;
const lli inf = 1e16;
pair<int, int> cows[maxN];
lli dist(int i, int j)
{
  return(abs(cows[i].first - cows[j].first) + abs(cows[i].second - cows[j].second));
}

struct Node
{
  lli full, cutLeft, cutMid, cutRight, lo, hi;
  Node operator+(const Node &a)
  {
    if (lo == inf) return(a);
    if (a.lo == inf) return(*this);
    if (a.hi - lo + 1 <= 3)
      return(Node({dist(lo, lo + 1) + dist(lo + 1, a.hi), dist(lo + 1, a.hi), dist(lo, a.hi), dist(lo, a.hi - 1), lo, a.hi}));
    lli ans = min({min(cutMid + a.full, full + a.cutMid) + dist(hi, a.lo),
                   cutRight + dist(max(lo, hi - 1), a.lo) + a.full,
                   full + dist(hi, min(a.lo + 1, a.hi)) + a.cutLeft,
                  });
    lli tot = full + a.full + dist(hi, a.lo);
    return(Node({tot, // full
                 tot - dist(lo, lo + 1), // cutLeft
                 ans, // cutMid
                 tot - dist(a.hi - 1, a.hi), // cutRight
                 lo, a.hi})); // lo, hi
  }
  void print()
  {
    printf("%lld %lld %lld %lld %lld %lld\n", full, cutLeft, cutMid, cutRight, lo, hi);
  }
};
Node segtree[4*maxN], nullNode = {0, 0, 0, 0, inf, inf};
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo >= hi)
  {
    segtree[i] = nullNode;
    segtree[i].lo = lo, segtree[i].hi = hi;
    DEBUG segtree[i].print();
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
  DEBUG segtree[i].print();
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > qhi || hi < qlo) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int pos, pair<int, int> value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > pos || hi < pos) return;
  if (lo >= hi)
  {
    cows[pos] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  update(pos, value, 2*i, lo, mid), update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

lli bruteForce(int lo, int hi)
{
  if (hi - lo + 1 <= 3) return(dist(lo, hi));
  lli minimum = 0;
  for (int i = lo; i < hi; i ++) minimum += dist(i, i + 1);
  for (int i = lo + 1; i < hi; i ++)
  {
    lli left = 0, right = 0;
    for (int j = 0; j < i - 1; j ++) left += dist(j, j + 1);
    for (int j = i + 1; j < hi; j ++) right += dist(j, j + 1);
    minimum = min(minimum, left + right + dist(i - 1, i + 1));
  }
  return(minimum);
}

int main()
{
  FILE *inputFile = fopen("marathon.in", "rb");
  FILE *outputFile = fopen("marathon.out", "wb");

  fscanf(inputFile, "%d %d", &n, &q);
  for (int i = 0; i < n; i ++) fscanf(inputFile, "%d %d", &cows[i].first, &cows[i].second);
  build();
  DEBUG printf("---------------\n");

  while (q --)
  {
    char op; fscanf(inputFile, " %c", &op);
    if (op == 'Q')
    {
      int lo, hi; fscanf(inputFile, "%d %d", &lo, &hi); lo --, hi --;
      DEBUG {
        query(lo, hi).print();
        fprintf(outputFile, "%lld - %lld\n", query(lo, hi).cutMid, bruteForce(lo, hi));
      } else
        fprintf(outputFile, "%lld\n", query(lo, hi).cutMid);
    }
    else
    {
      int pos, x, y; fscanf(inputFile, "%d %d %d", &pos, &x, &y); pos --;
      update(pos, {x, y});
    }
  }

  fclose(inputFile);
  fclose(outputFile);

  return(0);
}