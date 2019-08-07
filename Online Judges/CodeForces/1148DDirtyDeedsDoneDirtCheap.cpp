#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 3e5; int n;
pair<int, int> a[maxN];
vector<pair<int, int>> big, small;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &a[i].first, &a[i].second);
    if (a[i].first > a[i].second) big.push_back({a[i].second, i + 1});
    else small.push_back({-a[i].first, i + 1});
  }

  vector<pair<int, int>> ans = big.size() > small.size() ? big : small;
  sort(ans.begin(), ans.end());
  printf("%d\n", (int) ans.size());
  for (int i = 0; i < ans.size(); i ++)
    printf("%d%c", ans[i].second, i < ans.size() - 1 ? ' ' : '\n');

  return(0);
}