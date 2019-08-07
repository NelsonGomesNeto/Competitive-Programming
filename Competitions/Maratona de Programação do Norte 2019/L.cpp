#include <bits/stdc++.h>
using namespace std;

int main()
{
  int k; scanf("%d", &k);
  char des[k + 1]; scanf(" %s", des);

  int cnt[26][k], n; scanf("%d", &n);
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < n; i ++)
  {
    char ans[k + 1]; scanf(" %s", ans);
    for (int j = 0; j < k; j ++) cnt[ans[j] - 'A'][j] ++;
  }

  int ans = 0;
  for (int i = 0; i < k; i ++)
  {
    int best = 0;
    for (int j = 0; j < 26; j ++)
      if (des[i] != j + 'A')
        best = max(best, cnt[j][i]);
    ans += best;
  }
  printf("%d\n", ans);

  return(0);
}