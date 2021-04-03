#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, t, q;
int x[maxN], pos[maxN + 1];
int prv[maxN], prv2[maxN];
int totalQ = 0;

struct Triple
{
  int a, b, c;
  bool operator<(const Triple &other) const { return a < other.a || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c); }
};
map<Triple, int> memo;
int query(int a, int b, int c)
{
  Triple triple = Triple{a, b, c};
  if (memo.count(triple))
    return memo[triple];
  assert(++totalQ <= q);
  printf("%d %d %d\n", a, b, c); fflush(stdout);
  int res; scanf("%d", &res);
  return memo[triple] = res;
}

int main()
{
  scanf("%d %d %d", &t, &n, &q);
  for (int tt = 1; tt <= t; tt++)
  {
    memo.clear();
    for (int i = 0; i < n; i++)
      x[i] = i + 1;
    for (int i = 0; i < n; i++)
      pos[x[i]] = i;

    for (int k = 0; k < 12; k++)
    {
      DEBUG printf("#\ttriples:\n");
      int a = 1, b = 2, c = 3, it = 0;
      while (true)
      {
        int res = query(x[a - 1], x[b - 1], x[c - 1]);
        if (res == x[a - 1])
          swap(x[a - 1], x[b - 1]);
        else if (res == x[c - 1])
          swap(x[c - 1], x[b - 1]);

        a++, b++, c++;
        if (c == n + 1)
        {
          a = 1, b = 2, c = 3;
          it++;
        }
        if (it == 1)
          break;
      }

      DEBUG {
        printf("#\tnow: ");
        for (int i = 0; i < n; i++)
          printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
        fflush(stdout);
      }

      DEBUG printf("#\tquadruples:\n");
      a = 1, b = 2, c = 3; int d = 4;
      while (true)
      {
        int res1 = query(x[a - 1], x[b - 1], x[c - 1]);
        int res2 = query(x[b - 1], x[c - 1], x[d - 1]);
        if (res1 == res2)
        {
          if (x[b - 1] == res1)
            swap(x[a - 1], x[c - 1]);
          else if (x[c - 1] == res1)
          {
            swap(x[a - 1], x[b - 1]);
            swap(x[b - 1], x[c - 1]);
            swap(x[c - 1], x[d - 1]);
          }
          else
            swap(x[b - 1], x[d - 1]);
        }

        a++, b++, c++, d++;
        if (d == n + 1)
          break;
      }

      DEBUG {
        printf("#\tnow: ");
        for (int i = 0; i < n; i++)
          printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
        fflush(stdout);
      }
    }

    for (int i = 0; i < n; i++)
      printf("%d%c", x[i], i < n - 1 ? ' ' : '\n');
    fflush(stdout);

    int verdict; scanf("%d", &verdict);
  }
  return 0;
}