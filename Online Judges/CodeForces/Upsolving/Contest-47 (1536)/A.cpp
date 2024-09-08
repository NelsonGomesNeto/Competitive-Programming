#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    bool can = true;
    set<int> ans;
    for (int i = 0; i < n; i++)
    {
      if (ans.count(a[i])) can = false;
      ans.insert(a[i]);
    }

    for (int i = 0; i < a.size(); i++)
      for (int j = 0; j < a.size(); j++)
      {
        int now = abs(a[i] - a[j]);
        if (!ans.count(now))
        {
          if (a.size() < 300)
            a.push_back(now), ans.insert(now);
          else
            can = false;
        }
      }

    if (can)
    {
      printf("YES\n%d\n", (int)a.size());
      for (int i = 0; i < a.size(); i++)
        printf("%d%c", a[i], i < a.size() - 1 ? ' ' : '\n');
    }
    else printf("NO\n");
  }
  return 0;
}
