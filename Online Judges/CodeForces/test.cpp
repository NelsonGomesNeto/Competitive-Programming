#include <bits/stdc++.h>
#define DEBUG if(1)

int main()
{
  int p[14]; for (int i = 0; i < 14; i ++) scanf("%d", &p[i]);
  int n[14], best = 0;
  for (int i = 0; i < 14; i ++)
  {
    for (int j = 0; j < 14; j ++) n[j] = p[j];
    n[i] = 0;
    for (int j = 1; j <= p[i]; j ++)
    {
      int pos = (i + j) % 14;
      n[pos] ++;
    }
    DEBUG for (int j = 0; j < 14; j ++) printf("%d%c", n[j], j < 14 - 1 ? ' ' : '\n');
    int now = 0;
    for (int j = 0; j < 14; j ++) now += !(n[j] & 1) ? n[j] : 0;
    if (now > best) best = now;
  }

  printf("%d\n", best);

  return(0);
}