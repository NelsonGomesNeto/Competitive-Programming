#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, k;
int a[maxN];

bool done()
{
  for (int i = 0; i < n; i++)
    if (a[i] != 0)
      return false;
  return true;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &k);
      for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

      if (k == 1)
      {
        if (a[0] == a[n - 1]) printf("1\n");
        else printf("-1\n");
      }
      else
      {
        int ans = 0;
        do
        {
          set<int> hehe;
          for (int i = 0; i < n && hehe.size() < k; i++)
          {
            hehe.insert(a[i]);
            a[i] = 0;
          }
          for (int i = 0; i < n; i++)
            if (a[i])
              a[i] -= *hehe.rbegin();
          ans++;
        }
        while (!done());
        printf("%d\n", ans);
      }
    }
  return 0;
}