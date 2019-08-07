#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  pair<int, int> a[n]; int total = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i].first);
    a[i].second = i + 1;
    total += a[i].first;
  }
  sort(a, a+n);

  int now = 0; vector<int> b;
  for (int i = n - 1; i >= 0; i --)
  {
    now += a[i].first;
    total -= a[i].first;
    b.push_back(a[i].second);
    if (now > total) break;
  }

  if (total <= 0) printf("-1\n");
  else
  {
    printf("%d\n", (int) b.size());
    for (int i = 0; i < b.size(); i ++)
      printf("%d%c", b[i], i < b.size() - 1 ? ' ' : '\n');
  }
  return(0);
}