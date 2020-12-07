#include <bits/stdc++.h>
using namespace std;

int main()
{
  char s[(int) 1e6 + 1], ss[(int) 1e6 + 1]; scanf("%s", s);
  int open = 0, close = 0, size; int all[(int) 1e6 + 1]; memset(all, 0, sizeof(all));
  for (int i = 0; s[i]; i ++)
  {
    if (s[i] == '(') open ++, size ++;
    else
    {
      open --, close ++;
      if (open >= 0) all[close * 2] ++;
    }
    // printf("%d %d\n", open, close);
    if (open < 0) open = close = 0;
  }

  int maximum = 0;
  for (int i = 0; i <= 1e6; i ++)
    if (all[i]) maximum = i;

  reverse(s, s+strlen(s));
  open = 0, close = 0, size; memset(all, 0, sizeof(all));
  for (int i = 0; s[i]; i ++)
  {
    if (s[i] == '(') open ++, size ++;
    else
    {
      open --, close ++;
      if (open >= 0) all[close * 2] ++;
    }
    // printf("%d %d\n", open, close);
    if (open < 0) open = close = 0;
  }

  int m2 = 0;
  for (int i = 0; i <= 1e6; i ++)
    if (all[i]) m2 = i;
  int ans = min(maximum, m2);
  printf("%d %d\n", ans, ans == 0 ? 1 : all[ans]);

  return(0);
}
