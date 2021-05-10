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
    int n, x; scanf("%d %d", &n, &x);
    vector<int> w(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &w[i]);
    sort(w.begin(), w.end(), greater<int>());

    bool can = true;
    vector<int> ans = w;
    for (int i = 0, sum = 0; i < n; i++)
    {
      sum += ans[i];
      if (sum == x)
      {
        sum -= ans[i];
        swap(ans[i], ans.back());
        sum += ans[i];
      }
    }

    for (int i = 0, sum = 0; i < n; i++)
    {
      sum += ans[i];
      if (sum == x)
        can = false;
    }

    if (can)
    {
      printf("YES\n");
      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
    else
      printf("NO\n");
  }
  return 0;
}
