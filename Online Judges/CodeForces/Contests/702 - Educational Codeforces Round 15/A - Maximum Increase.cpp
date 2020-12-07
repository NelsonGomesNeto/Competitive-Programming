#include <bits/stdc++.h>
int inf = 1e9;

int main()
{
  int size; scanf("%d", &size);
  int num, ans = 0, now = 0, prev = -inf;
  for (int i = 0; i < size; i ++)
  {
    scanf("%d", &num);
    if (num > prev) now ++;
    else now = 1;
    if (now > ans) ans = now;
    prev = num;
  }

  printf("%d\n", ans);

  return(0);
}