#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5 + 1; int n;
int a[maxN], leftMost[maxN], rightMost[maxN];
vector<int> b;

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    b.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.resize(distance(b.begin(), unique(b.begin(), b.end())));

    for (int i = 0; i < n; i ++) rightMost[a[i]] = i;
    for (int i = n - 1; i >= 0; i --) leftMost[a[i]] = i;

    int ans = b.size() - 1;
    for (int i = 1, now = 1; i < b.size(); i ++)
    {
      if (rightMost[b[i - 1]] > leftMost[b[i]]) now = 1;
      else now ++;
      ans = min(ans, (int) b.size() - now);
    }
    printf("%d\n", ans);
  }
  return 0;
}
