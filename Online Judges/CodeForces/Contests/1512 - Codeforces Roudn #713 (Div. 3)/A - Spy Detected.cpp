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

    vector<int> pos[100 + 1];
    for (int i = 0; i < n; i++)
      pos[a[i]].push_back(i);

    int ans;
    for (int i = 0; i < n; i++)
      if (pos[a[i]].size() == 1)
        ans = pos[a[i]].back();
    printf("%d\n", ans + 1);
  }
  return 0;
}
