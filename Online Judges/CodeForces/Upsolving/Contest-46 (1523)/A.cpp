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
    int n, m; scanf("%d %d", &n, &m);
    char a[n + 1], ans[n + 1];
    scanf(" %s", a);


    ans[n] = '\0';
    for (int i = 0; i < n; i++)
    {
      if (a[i] == '0')
      {
        int r = i + 1;
        while (r < n && a[r] != '1') r++;
        int l = i - 1;
        while (l >= 0 && a[l] != '1') l--;

        int rDist = 1e9 + 1, lDist = 1e9 + 1;
        if (r < n && a[r] == '1') rDist = abs(i - r) + 0;
        if (l >= 0 && a[l] == '1') lDist = abs(i - l) + 0;
        if (min(rDist, lDist) <= m && (rDist == 1e9 + 1 || lDist == 1e9 + 1 || lDist != rDist))
          ans[i] = '1';
        else
          ans[i] = '0';
      }
      else
        ans[i] = '1';
    }
    printf("%s\n", ans);
  }
  return 0;
}
