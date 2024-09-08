#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
__int128 a[maxN], acc[maxN + 1], x;

__int128 sum(__int128 pos)
{
  __int128 total = acc[n] * (pos / n);
  total += acc[1 + pos % n];
  return total;
}

__int128 read()
{
  __int128 x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(__int128 x)
{
  if (x < 0)
  {
    putchar('-');
    x = -x;
  }
  if (x > 9) print(x / 10);
  putchar(x % 10 + '0');
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      a[i] = read();
      acc[i + 1] = acc[i] + a[i];
    }
    x = read();

    __int128 lo = 0, hi = 1e18 + 2;
    while (lo < hi)
    {
      __int128 mid = (lo + hi) >> 1;
      __int128 s = sum(mid);
      if (s > x) hi = mid;
      else lo = mid + 1;
    }
    // printf("%lld\n", lo + 1);
    print(lo + 1); printf("\n");
  }
  return 0;
}