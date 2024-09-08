#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
int a[2*maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    if (n <= 4)
    {
      if (n == 2) printf("-1\n");
      if (n == 3) printf("-1\n");
      if (n == 4) printf("3 1 4 2\n");
      continue;
    }
    bool can = false;
    int i, p;
    for (i = 0, p = n; p >= 1; i++, p -= 2)
      a[i] = p;

    if (n & 1)
    {
      a[i] = 4, a[i + 1] = 2, p = 6;
      for (i = i + 2; i < n; i++, p += 2)
        a[i] = p;
    }
    else
    {
      a[i] = 5, a[i + 1] = 1, a[i + 2] = 3, p = 7;
      for (i = i + 3; i < n; i++, p += 2)
        a[i] = p;
    }

    DEBUG {
      set<int> has;
      bool valid = true;
      for (int i = 0; i < n - 1; i++)
      {
        if (has.count(a[i])) valid = false;
        has.insert(a[i]);
        valid &= a[i] >= 1 && a[i] <= n && a[i + 1] >= 1 && a[i + 1] <= n && abs(a[i] - a[i + 1]) >= 2 && abs(a[i] - a[i + 1]) <= 4;
      }
      if (has.count(a[n - 1])) valid = false;

      DEBUG printf("\t%d %d\n", n, valid);
      assert(valid);
    }
    for (int i = 0; i < n; i++)
      printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}