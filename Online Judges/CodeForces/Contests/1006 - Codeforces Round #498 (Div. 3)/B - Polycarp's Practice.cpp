#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  pair<int, int> a[n]; for (int i = 0; i < n; i ++) { scanf("%d", &a[i].first); a[i].second = i; }
  sort(a,a+n);

  vector<pair<int, int> > ans;
  for (int i = n - 1; ans.size() < k; i --) ans.push_back({a[i].second, a[i].first});
  sort(ans.begin(), ans.end());

  DEBUG for (int i = 0; i < k; i ++) printf("%d %d\n", ans[i].first, ans[i].second);

  int sum = 0;
  for (int i = 0; i < k; i ++) sum += ans[i].second;
  printf("%d\n", sum);

  for (int i = 0, prev, next; i < k; i ++)
  {
    prev = i > 0 ? ans[i].first : 0;
    next = i + 1 < k ? ans[i + 1].first - 1: n - 1;
    DEBUG printf("%d %d %d\n", prev, next, next - prev + 1);
    printf("%d%c", next - prev + 1, i < k - 1 ? ' ' : '\n');
  }

  return(0);
}
