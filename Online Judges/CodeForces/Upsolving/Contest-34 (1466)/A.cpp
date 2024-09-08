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
    int x[n]; for (int i = 0; i < n; i++) scanf("%d", &x[i]);

    set<double> areas;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        double b = x[j], h = 1;
        double a = b * h / 2 - x[i] * h / 2;
        areas.insert(a);
      }

    if (areas.count(0)) areas.erase(0);
    printf("%d\n", (int)areas.size());
  }
  return 0;
}
