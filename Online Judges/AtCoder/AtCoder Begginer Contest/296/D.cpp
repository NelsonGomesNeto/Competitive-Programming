#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli read()
{
  lli x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(lli x)
{
  if (x < 0)
  {
    putchar('-');
    x = -x;
  }
  if (x > 9)
    print(x / 10);
  putchar(x % 10 + '0');
}
bool cmp(lli x, lli y) { return x > y; }
lli bigabs(lli x) { return x < 0 ? -x : x; }

lli n, m;

int main()
{
  n = read();
  m = read();
  lli ans = LONG_LONG_MAX;
  for (lli a = 1, end = min(n, (lli)sqrt(2*m)); a <= end; ++a)
  {
    lli b = ceil((long double)m / a);
    if (b <= n && a * b >= m)
      ans = min(ans, a * b);
  }
  if (ans == LONG_LONG_MAX)
    ans = -1;
  print(ans);
  return 0;
}
