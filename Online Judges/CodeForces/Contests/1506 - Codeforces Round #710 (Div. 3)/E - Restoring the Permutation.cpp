#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int q[maxN];
int minimum[maxN], maximum[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    set<int> available;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &q[i]);
      available.insert(i + 1);
    }

    for (int i = 0; i < n; i++)
      minimum[i] = maximum[i] = -1;
    for (int i = n - 1; i >= 0; i--)
    {
      while (i - 1 >= 0 && q[i - 1] == q[i])
        i--;
      minimum[i] = maximum[i] = q[i], available.erase(q[i]);
    }

    set<int> mina = available;
    for (int i = 0; i < n; i++)
    {
      while (i < n && minimum[i] != -1)
        i++;
      while (i < n && minimum[i] == -1)
      {
        minimum[i++] = *mina.begin();
        mina.erase(mina.begin());
      }
    }

    set<int> maxa;
    for (int i: available)
      maxa.insert(-i);
    for (int i = 0; i < n; i++)
    {
      int base = -1;
      while (i < n && maximum[i] != -1)
      {
        base = maximum[i];
        i++;
      }
      if (i >= n) continue;
      assert(base != -1);
      while (i < n && maximum[i] == -1)
      {
        auto it = maxa.lower_bound(-base);
        maximum[i++] = -(*it);
        maxa.erase(it);
      }
      i--;
    }

    for (int i = 0; i < n; i++)
      printf("%d%c", minimum[i], i < n - 1 ? ' ' : '\n');
    for (int i = 0; i < n; i++)
      printf("%d%c", maximum[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
