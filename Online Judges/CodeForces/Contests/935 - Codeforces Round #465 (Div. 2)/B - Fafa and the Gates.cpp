#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d\n", &n);
  char l, prev = 'x'; int x = 0, y = 0, pay = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%c", &l);
    if (x == y && prev == l) pay ++;
    if (l == 'U') y ++;
    else x ++;
    prev = l;
  }
  printf("%d\n", pay);
  return(0);
}