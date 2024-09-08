#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<lli> x;
struct Segment
{
  lli l, r;
  void read()
  {
    scanf("%lld %lld", &l, &r);
    x.push_back(l);
    x.push_back(r);
  }
};
Segment segments[maxN];

const int maxX = 4e5;
int in[maxX], out[maxX];

int l[maxX], r[maxX];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    x.clear();
    for (int i = 0; i < n; i++)
      segments[i].read();

    sort(x.begin(), x.end());
    x.resize(distance(x.begin(), unique(x.begin(), x.end())));

    for (int i = 0; i < x.size(); i++) in[i] = out[i] = 0;
    for (int i = 0; i < n; i++)
    {
      segments[i].l = lower_bound(x.begin(), x.end(), segments[i].l) - x.begin();
      segments[i].r = lower_bound(x.begin(), x.end(), segments[i].r) - x.begin();
      in[segments[i].l]++;
      out[segments[i].r]++;

    }

    int curr = 0;
    for (int i = 0; i < x.size(); i++)
    {
      curr += out[i];
      l[i] = curr;
    }
    curr = 0;
    for (int i = x.size() - 1; i >= 0; i--)
    {
      curr += in[i];
      r[i] = curr;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      int left = segments[i].l > 0 ? l[segments[i].l - 1] : 0;
      int right = segments[i].r + 1 < x.size() ? r[segments[i].r + 1] : 0;
      DEBUG printf("%d - %d | %lld %lld - %d %d\n", i, n, segments[i].l, segments[i].r, left, right);
      ans = max(ans, n - (left + right));
    }

    DEBUG printf("\t%d\n", ans);
    printf("%d\n", max(0, n - ans));
  }
  return 0;
}
