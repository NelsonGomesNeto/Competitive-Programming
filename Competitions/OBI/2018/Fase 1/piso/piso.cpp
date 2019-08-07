#include <bits/stdc++.h>

int main()
{
  int l, c; scanf("%d %d", &l, &c);
  int t1 = l * c + (l - 1) * (c - 1);
  int t2 = (l - 1) * 2 + (c - 1) * 2;
  printf("%d %d\n", t1, t2);

  return(0);
}
