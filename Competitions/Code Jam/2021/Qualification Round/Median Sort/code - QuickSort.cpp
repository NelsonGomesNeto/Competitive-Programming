#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, t, q;
int x[maxN];
int totalQ = 0;

struct Triple
{
  int a, b, c;
  bool operator<(const Triple &other) const { return a < other.a || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c); }
};
map<Triple, int> memo;
int query(int a, int b, int c)
{
  vector<int> abc = {a, b, c};
  sort(abc.begin(), abc.end());
  Triple triple = Triple{abc[0], abc[1], abc[2]};
  if (memo.count(triple))
    return memo[triple];
  // assert(++totalQ <= q);
  printf("%d %d %d\n", a, b, c); fflush(stdout);
  int res; scanf("%d", &res);
  return memo[triple] = res;
}

// find the pivots' correct order
void sortPivots(int lo, int hi)
{
  if (lo != 0 || hi != n - 1)
  {
    if (lo != 0)
    {
      int res = query(x[0], x[lo], x[hi]);
      if (res == x[hi])
        swap(x[lo], x[hi]);
    }
    else
    {
      int res = query(x[lo], x[hi], x[n - 1]);
      if (res == x[lo])
        swap(x[lo], x[hi]);
    }
  }
}

void quickSort(int lo = 0, int hi = n - 1)
{
  if (lo >= hi - 1)
  {
    if (lo + 1 == hi)
    {
      sortPivots(lo, hi);
      DEBUG printf("#\t sort 2: %d %d\n", lo, hi);
    }
    return;
  }

  int leftPivot = lo, rightPivot = hi;
  sortPivots(leftPivot, rightPivot);

  vector<int> l, m, r;
  for (int i = lo; i <= hi; i++)
  {
    if (i == leftPivot || i == rightPivot)
      continue;

    int res = query(x[leftPivot], x[i], x[rightPivot]);

    if (res == x[leftPivot])
      l.push_back(x[i]);
    else if (res == x[rightPivot])
      r.push_back(x[i]);
    else
      m.push_back(x[i]);
  }
  l.push_back(x[leftPivot]);
  m.push_back(x[rightPivot]);

  {
    int i = lo;
    for (int j: l) x[i++] = j;
    for (int j: m) x[i++] = j;
    for (int j: r) x[i++] = j;
  }

  DEBUG {
    printf("#\tnow %d %d | %d %d | x: ", lo, hi, leftPivot, rightPivot);
    for (int i = 0; i < n; i++)
      printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
    printf("#\t\tl: ");
    for (int i = 0; i < l.size(); i++)
      printf("%d%c", l[i], i < l.size() - 1 ? ' ' : '\n');
    printf("#\t\tm: ");
    for (int i = 0; i < m.size(); i++)
      printf("%d%c", m[i], i < m.size() - 1 ? ' ' : '\n');
    printf("#\t\tr: ");
    for (int i = 0; i < r.size(); i++)
      printf("%d%c", r[i], i < r.size() - 1 ? ' ' : '\n');
    fflush(stdout);
  }

  quickSort(lo, lo + l.size() - 2); // [lo : leftPivot final pos - 1]
  quickSort(lo + l.size(), hi - r.size() - 1); // [leftPivot final pos + 1 : rightPivot final pos - 1]
  quickSort(hi - r.size() + 1, hi); // [rightPivot final pos + 1 : hi]
}

int main()
{
  srand(time(NULL));

  scanf("%d %d %d", &t, &n, &q);
  for (int tt = 1; tt <= t; tt++)
  {
    memo.clear();
    for (int i = 0; i < n; i++)
      x[i] = i + 1;

    quickSort();

    for (int i = 0; i < n; i++)
      printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
    fflush(stdout);

    int verdict; scanf("%d", &verdict);
  }
  return 0;
}