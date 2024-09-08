#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

void fastReadInt(int &x)
{
  bool neg = false;
  int c = ' ';
  x = 0;
  while (c != '-' && (c < '0' || c > '9'))
    c = getchar();
 
  if (c == '-')
    neg = true, c = getchar();
 
  for ( ; (c > 47 && c < 58); c = getchar())
    x = (x<<1) + (x<<3) + c - 48;
  if (neg)
    x *=-1;
}

const int maxN = 1e6; int n, m;
int a[maxN], b[maxN];
vector<int> as, bs;

void makeUnique(vector<int> &arr)
{
  sort(arr.begin(), arr.end());
  arr.resize(distance(arr.begin(), unique(arr.begin(), arr.end())));
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) fastReadInt(a[i]);
    for (int i = 0; i < m; i++) fastReadInt(b[i]);

    as.clear();
    for (int i = 0; i < n; i++) as.push_back(a[i]);
    makeUnique(as);
    bs.clear();
    for (int i = 0; i < m; i++) bs.push_back(b[i]);
    makeUnique(bs);

    if (as.size() == 1) printf("Yes\n");
    else
    {
      lli g = as[1] - as[0];
      for (int i = 2; i < as.size(); i++)
        g = gcd(g, as[i] - as[i - 1]);

      DEBUG printf("%lld\n", g);
      bool can = false;

      lli gg = bs[0];
      for (int i = 1; i < bs.size(); i++)
        gg = gcd(gg, bs[i]);

      if (g % gg == 0)
        can = true;

      printf("%s\n", can ? "Yes" : "No");
    }
  }
  return 0;
}