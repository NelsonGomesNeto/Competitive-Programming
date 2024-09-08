#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 999; int n;
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    bool sorted = true;
    for (int i = 0; i < n; i++)
      if (a[i] != i + 1)
      {
        sorted = false;
        break;
      }
    int ans = 0;
    while (!sorted)
    {
      for (int i = ans & 1; i + 1 < n; i += 2)
        if (a[i] > a[i + 1])
          swap(a[i], a[i + 1]);

      sorted = true;
      for (int i = 0; i < n; i++)
        if (a[i] != i + 1)
        {
          sorted = false;
          break;
        }
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
