#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int x, y, left = 0, right = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &x, &y);
    left += x < 0; right += x > 0;
  }

  printf("%s\n", left + 1 >= n || right + 1 >= n ? "Yes" : "No");

  return(0);
}