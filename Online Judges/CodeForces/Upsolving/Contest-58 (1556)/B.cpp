#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN], aux[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      aux[i] = a[i];
    }

    int p[2] = {0, 0};
    for (int i = 0; i < n; i++)
      p[a[i] & 1]++;

    if (abs((int)p[0] - (int)p[1]) > 1)
      printf("-1\n");
    else
    {
      int ans = 0;
      for (int i = 0; i + 1 < n; i++)
      {
        if ((a[i] & 1) == (a[i + 1] & 1))
        {
          int j = i + 2;
          while (j < n && (a[j] & 1) == (a[i] & 1)) j++;
          if (j < n && (a[j] & 1) != (a[i] & 1))
          {
            ans += j - i - 1;
            swap(a[i + 1], a[j]);
          }
        }
      }

      for (int i = 0; i + 1 < n; i++)
        if ((a[i] & 1) == (a[i + 1] & 1))
          ans = -1;

      if (ans == -1)
      {
        for (int i = 0; i < n; i++) a[i] = aux[i];
        reverse(a, a+n);

        ans = 0;
        for (int i = 0; i + 1 < n; i++)
        {
          if ((a[i] & 1) == (a[i + 1] & 1))
          {
            int j = i + 2;
            while (j < n && (a[j] & 1) == (a[i] & 1)) j++;
            if (j < n && (a[j] & 1) != (a[i] & 1))
            {
              ans += j - i - 1;
              swap(a[i + 1], a[j]);
            }
          }
        }

        for (int i = 0; i + 1 < n; i++)
          assert((a[i] & 1) != (a[i + 1] & 1));
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
