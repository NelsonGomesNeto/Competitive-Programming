#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, d;
int num[maxN], ans[maxN], s[maxN];

int main()
{
  while (scanf("%d %d", &n, &d) != EOF && !(n == 0 && d == 0))
  {
    for (int i = 0; i < n; i ++) scanf("%1d", &num[i]);
    int sp = -1;
    for (int i = 0; i < n; i ++)
    {
      while (sp > -1 && d && num[i] > s[sp])
        sp --, d --;
      s[++ sp] = num[i];
    }
    while (d) sp --, d --;

    int i;
    for (i = 0; sp > -1; i ++) ans[i] = s[sp --];
    reverse(ans, ans+i);
    for (int j = 0; j < i; j ++) printf("%d", ans[j]); printf("\n");
  }
  return(0);
}