#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
#define lli long long int
lli levelEnergy[(int) 1e5], neededEnergy[(int) 1e5 + 1];

/* Explantion:
First: for each store, calculate the level that can be reached from the store's level
  This can be done with a binary search
Second: sort stores by level they appear, there's no need to handle ties

Now we can apply a greedy strategy with a min segtree
update position 0 with 0; since we can always reach level 0 (yes, I will label levels from 0 to n-1)
for each store in stores:
  needed = query(from store.level to n)
    the minimum amount of money needed to reach store.level will the the minimum
    of reaching any level from store.level and beyond
  update(at store.reaches with needed + store.cost)
    then further stores can consider this store (if it's good) to go even further
ans = query(from n to n)
*/

int binSearch(int lo, int hi, lli energy)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (energy < neededEnergy[mid]) return(binSearch(lo, mid - 1, energy));
  return(binSearch(mid, hi, energy));
}

lli segtree[(int) 4e5], inf = 1e18;
int pos; lli value;
void update(int lo, int hi, int i = 1)
{
  if (lo > pos || hi < pos) return;
  if (lo >= hi)
  {
    segtree[i] = min(segtree[i], value);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(lo, mid, 2*i); update(mid + 1, hi, 2*i + 1);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}
int qlo, qhi;
lli query(int lo, int hi, int i = 1)
{
  if (lo > qhi || hi < qlo) return(inf);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(min(query(lo, mid, 2*i), query(mid + 1, hi, 2*i + 1)));
}

struct Store { int level; lli energy, cost; int reaches; };
Store stores[(int) 1e5];
int comp(const Store &a, const Store &b)
{
  return(a.level < b.level);
}

int main()
{
  for (int i = 0; i < 4e5; i ++) segtree[i] = inf;
  int n, m; scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%lld", &levelEnergy[i]);
  neededEnergy[0] = 0;
  for (int i = 1; i <= n; i ++) neededEnergy[i] = neededEnergy[i - 1] + levelEnergy[i - 1];
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %lld %lld", &stores[i].level, &stores[i].energy, &stores[i].cost);
    stores[i].level --;
    stores[i].reaches = binSearch(0, n, stores[i].energy + neededEnergy[stores[i].level]);
  }
  sort(stores, stores+m, comp);

  DEBUG
  {
    for (int i = 0; i <= n; i ++) printf("%lld%c", neededEnergy[i], i < n ? ' ' : '\n');
    for (int i = 0; i < m; i ++)
      printf("%d %lld %lld %d\n", stores[i].level, stores[i].energy, stores[i].cost, stores[i].reaches);
  }

  pos = 0, value = 0; update(0, n);
  for (int i = 0; i < m; i ++)
  {
    qlo = stores[i].level, qhi = n;
    lli needed = query(0, n);
    pos = stores[i].reaches, value = needed + stores[i].cost;
    update(0, n);
  }
  qlo = qhi = n;
  lli ans = query(0, n);
  if (ans == inf) printf("-1\n");
  else printf("%lld\n", ans);

  return(0);
}
