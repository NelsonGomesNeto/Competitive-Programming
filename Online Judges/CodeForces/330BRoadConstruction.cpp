#include <bits/stdc++.h>

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int restrictions[n]; memset(restrictions, 0, sizeof(restrictions));
  for (int i = 0; i < m; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --; v --;
    restrictions[u] ++; restrictions[v] ++;
  }
  int dot = -1;
  for (int i = 0; i < n && dot == -1; i ++)
    if (!restrictions[i])
      dot = i;

  printf("%d\n", n - 1);
  for (int i = 0; i < n; i ++)
    if (i != dot)
      printf("%d %d\n", i + 1, dot + 1);

  return(0);
}