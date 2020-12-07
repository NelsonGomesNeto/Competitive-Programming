#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d\n", &n);
  char string[n + 1]; scanf("%s", string);
  int i, x = 0, y = 0;
  for (i = 0; i < n; i ++)
  {
    if (string[i] == 'L') x --;
    if (string[i] == 'R') x ++;
    if (string[i] == 'U') y ++;
    if (string[i] == 'D') y --;
  }

  int dist = abs(y) + abs(x);

  printf("%d\n", abs(n - dist));

  return(0);
}