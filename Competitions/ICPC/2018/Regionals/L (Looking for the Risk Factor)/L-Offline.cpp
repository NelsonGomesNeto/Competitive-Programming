#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 1e5;
int segtree[4*(maxN + 1)], marked[maxN + 1]; int n = maxN + 1;
void build(int lo = 0, int hi = n - 1, int i = 1)
{
  if (lo == hi)
  {
    marked[lo] = segtree[i] = 1;
    return;
  }
  int mid = (lo + hi) >> 1;
  build(lo, mid, 2*i); build(mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
void update(int value, int pos, int lo = 0, int hi = n - 1, int i = 1)
{
  if (lo == hi)
  {
    marked[lo] = segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (lo <= pos && pos <= mid) update(value, pos, lo, mid, 2*i);
  else update(value, pos, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
int query(int qlo, int qhi, int lo = 0, int hi = n - 1, int i = 1)
{
  if (qlo <= lo && hi <= qhi) return(segtree[i]);
  if (hi < qlo || lo > qhi) return(0);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, lo, mid, 2*i) + query(qlo, qhi, mid + 1, hi, 2*i + 1));
}

struct Query
{
  int n, k, i;
  bool operator<(const Query &a) const { return(k > a.k); }
};
vector<Query> queries; int ans[maxN + 1];

bool notPrime[maxN + 1];
vector<int> primes;
void sieve()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i ++)
    for (int j = 2; i*j <= maxN; j ++)
      notPrime[i*j] = true;
  for (int i = 2; i <= maxN; i ++)
    if (!notPrime[i])
      primes.push_back(i);
}

void solve()
{
  for (int q = 0, i = primes.size() - 1; q < queries.size(); q ++)
  {
    for (; primes[i] > queries[q].k; i --)
      for (int j = 1; j*primes[i] <= maxN; j ++)
        if (marked[j*primes[i]])
          update(0, j*primes[i]);
    DEBUG printf("%d %d %d %d\n", primes[i], queries[q].k, queries[q].n, query(2, queries[q].n));
    ans[queries[q].i] = query(2, queries[q].n);
  }
}

int main()
{
  sieve(); build();
  int q; scanf("%d", &q);
  for (int i = 0, n, k; i < q; i ++)
  {
    scanf("%d %d", &n, &k);
    queries.push_back({n, k, i});
  }
  sort(queries.begin(), queries.end());
  solve();
  for (int i = 0; i < q; i ++)
    printf("%d\n", ans[i]);
  return(0);
}