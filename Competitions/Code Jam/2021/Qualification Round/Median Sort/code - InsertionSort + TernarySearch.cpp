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

void insertionSort()
{
  vector<int> ans;
  int base = query(1, 2, 3);
  if (base == 1) ans = {2, 1, 3};
  if (base == 2) ans = {1, 2, 3};
  if (base == 3) ans = {1, 3, 2};

  vector<int> aux;
  for (int i = 4; i <= n; i++)
    aux.push_back(i);
  // unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  // default_random_engine e(seed);
  // shuffle(aux.begin(), aux.end(), e);

  for (int ii: aux)
  {
    int i = ii;
    bool done = false;
    int lo = 0, hi = ans.size() - 1;
    while (lo < hi - 2)
    {
      int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
      int res = query(ans[midlo], i, ans[midhi]);
      if (res == i && (hi - lo + 1) == 3)
      {
        ans.insert(ans.begin() + midlo + 1, i);
        done = true;
        break;
      }
      else if (res == ans[midlo]) hi = midlo;
      else if (res == ans[midhi]) lo = midhi;
      else lo = midlo, hi = midhi;
    }

    if (!done)
      while (lo < hi)
      {
        int mid = (lo + hi) >> 1;
        int res = query(ans[mid], i, ans[mid + 1]);
        if (res == i)
        {
          ans.insert(ans.begin() + mid + 1, i);
          done = true;
          break;
        }
        else if (res == ans[mid]) hi = mid;
        else lo = mid + 1;
      }

    if (!done)
    {
      if (lo == 0) ans.insert(ans.begin(), i);
      else ans.insert(ans.end(), i);
    }
  }

  for (int i = 0; i < n; i++)
    x[i] = ans[i];
}

int main()
{
  scanf("%d %d %d", &t, &n, &q);
  for (int tt = 1; tt <= t; tt++)
  {
    memo.clear();
    for (int i = 0; i < n; i++)
      x[i] = i + 1;

    insertionSort();

    for (int i = 0; i < n; i++)
      printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
    fflush(stdout);

    int verdict; scanf("%d", &verdict);
  }
  return 0;
}