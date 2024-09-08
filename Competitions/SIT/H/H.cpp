#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<lli> a[2], acc[2];

int main()
{
  while (~scanf("%d"))
  {
    a[0].clear(), a[1].clear();

    for (int i = 0; i < n; i++)
    {
      int c, t; scanf("%d %d", &c, &t);
      a[t - 1].push_back(c);
    }

    sort(a[0].begin(), a[0].end());
    sort(a[1].begin(), a[1].end());
    acc[0].resize(a[0].size() + 1, 0);
    acc[1].resize(a[1].size() + 1, 0);

    for (int i = 0; i < 2; i++)
      for (int j = 0; j < a[i].size(); j++)
        acc[i][j + 1] = acc[i][j] + a[i][j];

    /*
      bought x type 0
      bought y type 1
      

      [min(x, 2), x + 2*x + 2]
      [min(x, 2), 3*x + 2], y = [0, 2*(x + 1)]
    */
  }
  return 0;
}