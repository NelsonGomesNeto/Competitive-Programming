#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101; int n, r, p, s;
char aa[maxN + 1]; 
char ans[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    scanf("%d %d %d", &r, &p, &s);
    scanf(" %s", aa);

    memset(ans, '\0', sizeof(ans));
    int wins = 0;
    for (int i = 0; i < n; i ++)
      if (aa[i] == 'R' && p)
        p --, ans[i] = 'P', wins ++;
      else if (aa[i] == 'P' && s)
        s --, ans[i] = 'S', wins ++;
      else if (aa[i] == 'S' && r)
        r --, ans[i] = 'R', wins ++;
      else
        ans[i] = 'T';
    if (wins >= ((n + 1) >> 1))
    {
      printf("YES\n");
      for (int i = 0; i < n; i ++)
        if (ans[i] == 'T')
        {
          if (p) ans[i] = 'P', p --;
          else if (s) ans[i] = 'S', s --;
          else if (r) ans[i] = 'R', r --;
        }
      printf("%s\n", ans);
    }
    else
      printf("NO\n");
  }
  return 0;
}
