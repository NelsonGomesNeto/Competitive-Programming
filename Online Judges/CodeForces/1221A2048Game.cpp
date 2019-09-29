#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int cnt[2049];

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    int n; scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i ++)
    {
      int u; scanf("%d", &u);
      if (u <= 2048) cnt[u] ++;
    }

    for (int i = 0; (1 << i) < 2048; i ++)
      cnt[1 << (i + 1)] += cnt[1 << i] >> 1;

    printf("%s\n", cnt[2048] ? "YES" : "NO");
  }
  return(0);
}
