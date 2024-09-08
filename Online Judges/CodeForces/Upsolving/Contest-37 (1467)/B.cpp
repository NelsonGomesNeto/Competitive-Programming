#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];

lli l[maxN + 1], r[maxN + 1];

bool mountain(int i)
{
  return (a[i - 1] < a[i] && a[i + 1] < a[i]);
}
bool valley(int i)
{
  return (a[i - 1] > a[i] && a[i + 1] > a[i]);
}
bool is(int i)
{
  return (mountain(i) || valley(i));
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 1; i + 1 < n; i++)
      l[i + 1] = l[i] + is(i);

    r[n - 1] = 0;
    for (int i = n - 2; i > 0; i--)
      r[i] = r[i + 1] + is(i);

    int ans = 0;
    for (int i = 1; i + 1 < n; i++)
    {
      int before = 0, after1 = 0, after2 = 0;
      if (i - 1 >= 1) before += is(i - 1);
      if (i + 1 < n - 1) before += is(i + 1);
      if (i && i + 1 < n) before += is(i);

      lli aux = a[i];
      a[i] = a[i - 1];
      if (i - 1 >= 1) after1 += is(i - 1);
      if (i + 1 < n - 1) after1 += is(i + 1);
      if (i && i + 1 < n) after1 += is(i);

      a[i] = a[i + 1];
      if (i - 1 >= 1) after2 += is(i - 1);
      if (i + 1 < n - 1) after2 += is(i + 1);
      if (i && i + 1 < n) after2 += is(i);

      a[i] = aux;

      ans = max({ans, before - after1, before - after2});
    }
    ans = l[n - 1] - ans;

    printf("%d\n", ans);
  }
  return 0;
}
