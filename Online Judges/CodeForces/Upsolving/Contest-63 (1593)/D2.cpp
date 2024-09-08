#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n;
int a[maxN];
map<int, int> acnt;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    acnt.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      acnt[a[i]]++;
    }

    int msz = (n + 1) >> 1;

    set<int> dists;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        int d = abs(a[i] - a[j]);
        if (d) dists.insert(d);
      }

    set<int> ndists;
    for (int d: dists)
    {
      int sqd = sqrt(d);
      for (int i = 2; i <= sqd; i++)
        if (d % i == 0)
          ndists.insert(i), ndists.insert(d / i);
    }
    for (int nd: ndists) dists.insert(nd);

    bool can = false;
    for (int i = 0; i < n; i++)
      if (acnt[a[i]] >= msz)
        can = true;

    if (can)
      printf("-1\n");
    else
    {
      int ans = 1;
      for (int k: dists)
      {
        for (int i = 0; i < n; i++)
        {
          int cnt = 0;
          for (int j = 0; j < n; j++)
            if (a[i] <= a[j])
            {
              int delta = a[j] - a[i];
              if (delta % k == 0)
                cnt++;
            }
          DEBUG printf("\t%d %d %d\n", k, i, cnt);
          if (cnt >= msz)
            ans = k;
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
