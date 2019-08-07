#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int s[5], ss; memset(s, 0, sizeof(s));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &ss);
    s[ss] ++;
  }

  int taxis = s[4];
  while (s[1] && s[3])
  {
    taxis ++;
    s[1] --; s[3] --;
  }
  taxis += s[3];
  while (s[2] && s[1])
  {
    taxis ++;
    s[2] --; s[1] -= s[1] > 1 ? 2 : 1;
  }
  while (s[2])
  {
    taxis ++;
    s[2] -= s[2] > 1 ? 2 : 1;
  }
  while (s[1])
  {
    taxis ++;
    s[1] -= s[1] > 3 ? 4 : s[1] > 2 ? 3 : s[1] > 1 ? 2 : 1;
  }
  printf("%d\n", taxis);

  return(0);
}
