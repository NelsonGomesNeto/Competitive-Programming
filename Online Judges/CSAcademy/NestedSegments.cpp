#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int segment[n][2];
  for (int i = 0; i < n; i ++)
    scanf("%d %d", &segment[i][0], &segment[i][1]);

  int nested = 0;
  for (int i = 0; i < n ; i ++)
    for (int j = 0; j < n; j ++)
        if (segment[j][0] < segment[i][0] && segment[i][1] < segment[j][1])
        {
          nested ++;
          break;
        }

  printf("%d\n", nested);

  return(0);
}