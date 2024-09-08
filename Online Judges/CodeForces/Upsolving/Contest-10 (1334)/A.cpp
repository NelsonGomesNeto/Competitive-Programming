#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n; scanf("%d", &n);
    pair<int, int> a[n];
    for (int i = 0; i < n; i++)
      scanf("%d %d", &a[i].first, &a[i].second);

    bool can = a[0].first >= a[0].second;
    for (int i = 1; i < n; i++)
    {
      if (a[i - 1].first > a[i].first || a[i - 1].second > a[i].second)
        can = false;
      if (a[i].first < a[i].second)
        can = false;
      if (a[i].second - a[i - 1].second > a[i].first - a[i - 1].first)
        can = false;
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
