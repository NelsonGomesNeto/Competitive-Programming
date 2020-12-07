#include <bits/stdc++.h>
int ans[101], m, s;

int fill(int i, int size, int sum, int now, int w)
{
  if ((size - i) * 9 + now < sum) return(0);
  if (now > sum) return(0);
  if (i == size) return(sum == now);

  int k;
  for (k = w ? (!i && size != 1) : 9; w ? k <= 9 : k >= (!i && size != 1); w ? k ++ : k --)
  {
    ans[i] = k;
    if (fill(i + 1, size, sum, now + k, w))
      return(1);
  }

  return(0);
}

int main()
{
  scanf("%d %d", &m, &s);

  int can = fill(0, m, s, 0, 1);

  if (!can) printf("-1 -1\n");
  else
  {
    int i;
    for (i = 0; i < m; i ++) printf("%d", ans[i]);
    printf(" ");
    fill(0, m, s, 0, 0);
    for (i = 0; i < m; i ++) printf("%d", ans[i]);
    printf("\n");
  }

  return(0);
}