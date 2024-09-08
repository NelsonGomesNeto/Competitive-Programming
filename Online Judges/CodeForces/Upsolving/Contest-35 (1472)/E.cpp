#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int h[maxN], w[maxN];
vector<int> xx;

pair<int, int> hw[2*maxN], wh[2*maxN];
pair<int, int> lhw[2*maxN], lwh[2*maxN];
int ans[maxN];

void makeUnique(vector<int> &x)
{
  sort(x.begin(), x.end());
  x.resize(distance(x.begin(), unique(x.begin(), x.end())));
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    xx.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d %d", &h[i], &w[i]);
      xx.push_back(h[i]);
      xx.push_back(w[i]);
    }
    makeUnique(xx);

    for (int i = 0; i < n; i++)
    {
      h[i] = lower_bound(xx.begin(), xx.end(), h[i]) - xx.begin();
      w[i] = lower_bound(xx.begin(), xx.end(), w[i]) - xx.begin();
    }

    for (int i = 0; i < xx.size(); i++)
      hw[i] = make_pair((int)1e9 + 1, -1);
    for (int i = 0; i < xx.size(); i++)
      wh[i] = make_pair((int)1e9 + 1, -1);

    for (int i = 0; i < n; i++)
    {
      hw[h[i]] = min(hw[h[i]], make_pair(w[i], i));
      wh[w[i]] = min(wh[w[i]], make_pair(h[i], i));
    }

    for (int i = 0; i < xx.size(); i++)
    {
      if (i) lhw[i] = min(lhw[i - 1], hw[i]);
      else lhw[i] = hw[i];
    }
    for (int i = 0; i < xx.size(); i++)
    {
      if (i) lwh[i] = min(lwh[i - 1], wh[i]);
      else lwh[i] = wh[i];
    }

    for (int i = 0; i < n; i++)
    {
      DEBUG printf("\t%d %d\n", h[i], w[i]);
      ans[i] = -1;
      if (h[i] > 0)
      {
        if (lhw[h[i] - 1].first < w[i])
          ans[i] = lhw[h[i] - 1].second + 1;
        if (lwh[h[i] - 1].first < w[i])
          ans[i] = lwh[h[i] - 1].second + 1;
      }
      if (w[i] > 0)
      {
        if (lwh[w[i] - 1].first < h[i])
          ans[i] = lwh[w[i] - 1].second + 1;
        if (lhw[w[i] - 1].first < h[i])
          ans[i] = lhw[w[i] - 1].second + 1;
      }

    }
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
