#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n;
int a[maxN];

int query(int i, int j)
{
  printf("? %d %d\n", i + 1, j + 1); fflush(stdout);
  int res; scanf("%d", &res);
  return res;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) a[i] = -1;
    list<int> pos;
    for (int i = 0; i < n; i++) pos.push_back(i);
    while (pos.size() > 1)
    {
      int i = *pos.begin(), j = *next(pos.begin());
      int q1 = query(i, j);
      int q2 = query(j, i);
      if (q1 > q2)
        a[i] = q1, pos.erase(pos.begin());
      else
        a[j] = q2, pos.erase(next(pos.begin()));
    }

    set<int> missing;
    for (int i = 0; i < n; i++) missing.insert(i + 1);
    for (int i = 0; i < n; i++)
      if (a[i] != -1)
        missing.erase(a[i]);

    for (int i = 0; i < n; i++)
      if (a[i] == -1)
        a[i] = *missing.begin();

    printf("! ");
    for (int i = 0; i < n; i++)
      printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
    fflush(stdout);
  }
  return 0;
}
