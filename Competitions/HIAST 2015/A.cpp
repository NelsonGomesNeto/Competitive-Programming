#include <bits/stdc++.h>

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int p[2][3];
    for (int i = 0; i < 2; i ++) for (int j = 0; j < 3; j ++) scanf("%d", &p[i][j]);

    int i = 0;
    while (i < 3 && p[0][i] == p[1][i]) i ++;
    if (i == 3) printf("Tie\n");
    else printf("Player%d\n", p[0][i] > p[1][i] ? 2 : 1);
  }
  return(0);
}