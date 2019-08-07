#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4;
int in[maxN + 2], out[maxN + 2], sum[maxN + 2];

int main()
{
  int n, m, l; scanf("%d %d %d", &n, &m, &l);
  for (int i = 0; i < m; i ++)
  {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    if (c > l) in[a] ++, out[b] ++;
  }

  int now = 0;
  for (int i = 0; i <= n; i ++)
  {
    now += in[i];
    sum[i] = now;
    now -= out[i];
  }
  int inf = 1, big = -1;
  for (int i = 0; i <= n; i ++)
  {
    int end = i + 1;
    while (end <= n && sum[i] == sum[end]) end ++;
    if (sum[i] > inf || (sum[i] == inf && end - i > big))
      inf = sum[i], big = end - i;
    i = end - 1;
  }
  printf("%d\n", big);

  return(0);
}