#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int cnt[101]; memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
      cnt[a[i]]++;

    vector<int> ans;
    for (int i = 0; i <= 100; i++)
      if (cnt[i])
        ans.push_back(i), cnt[i]--;

    for (int i = 0; i <= 100; i++)
      while (cnt[i])
        ans.push_back(i), cnt[i]--;

    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
