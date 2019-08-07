#include <bits/stdc++.h>

int main()
{
  int n, k, q; scanf("%d %d %d", &n, &k, &q);
  int in[200001], out[200001], total[200001], lo, hi;
  memset(in, 0, sizeof(in)); memset(out, 0, sizeof(out));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &lo, &hi);
    in[lo] ++; out[hi] ++;
  }

  for (int i = 0, now = 0; i <= 200000; i ++)
  {
    now += in[i];
    total[i] = now >= k;
    now -= out[i];
  }

  int sum[200002]; sum[0] = 0;
  for (int i = i; i <= 200001; i ++)
  {
    sum[i] = total[i] + sum[i - 1];
  }

  while (q --)
  {
    scanf("%d %d", &lo, &hi);
    printf("%d\n", sum[hi] - sum[lo - 1]);
  }

  return(0);
}
