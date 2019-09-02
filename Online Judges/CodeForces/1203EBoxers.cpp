#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 150000; int n;
int a[maxN], cnt[maxN + 2];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);
  sort(a, a+n); reverse(a, a+n);

  for (int i = 0; i < n; i ++)
  {
    if (!cnt[a[i] + 1])
      cnt[a[i] + 1] ++;
    else if (!cnt[a[i]])
      cnt[a[i]] ++;
    else if (a[i] > 1 && !cnt[a[i] - 1])
      cnt[a[i] - 1] ++;
  }

  int ans = 0; for (int i = 1; i <= maxN + 1; i ++) ans += cnt[i] > 0;
  printf("%d\n", ans);

  return(0);
}
