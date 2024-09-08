#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n, x; scanf("%d %d", &n, &x);
    int a[n];
    set<int> done;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      done.insert(a[i]);
    }

    int ans = 1;
    for (; ans <= 300; ans++)
    {
      bool can = true;
      set<int> missing;
      for (int j = 1; j <= ans; j++)
        if (!done.count(j))
          missing.insert(j);
      if (missing.size() > x) can = false;
      if (!can) { ans--; break; }
    }
    printf("%d\n", ans);
  }
  return 0;
}
