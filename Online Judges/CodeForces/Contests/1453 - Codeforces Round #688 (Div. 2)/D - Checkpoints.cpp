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
    lli k; scanf("%lld", &k);
    if (k & 1) printf("-1\n");
    else
    {
      vector<int> ans;
      ans.push_back(1);

      k -= 2;
      for (lli bit = 60; bit >= 3; bit--)
        if (k >= (1LL << bit) - 2)
        {
          for (int i = 0; i <= bit - 3; i++)
            ans.push_back(0);
          ans.push_back(1);

          k -= (1LL << bit) - 2;
        }

      while (k)
      {
        ans.push_back(1);
        k -= 2;
      }

      printf("%d\n", (int)ans.size());
      for (int i = 0; i < ans.size(); i++)
        printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
    }
  }
  return 0;
}