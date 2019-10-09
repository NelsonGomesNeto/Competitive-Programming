#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
char s[maxN + 1];
int dx[256], dy[256];

lli a, b, xx, yy;

bool bruteForce(lli x, lli y, bool fillDiff = false)
{
  bool can = false;
  for (int j = 0; j < 1000 && !can; j ++)
  {
    for (int i = 0; i < n && !can; i ++)
    {
      if (x == a && y == b)
        can = true;
      x += dx[s[i]], y += dy[s[i]];
    }
    if (!j && fillDiff) xx = x, yy = y;
  }
  return can;
}

int main()
{
  dx['U'] = dx['D'] = dy['L'] = dy['R'] = 0;
  dy['U'] = dx['R'] = 1, dy['D'] = dx['L'] = -1;

  while (scanf("%lld %lld", &a, &b) != EOF)
  {
    scanf(" %s", s); n = strlen(s);

    bool can = bruteForce(0, 0, true);
    if (!can)
    {
      if ((b >= 0 && yy >= 0) || (b <= 0 && yy <= 0))
        can = bruteForce(yy != 0 ? xx * max(1LL, abs(b / yy) - 100) : xx, yy != 0 ? yy * max(1LL, abs(b / yy) - 100) : yy);
      if (!can && ((a >= 0 && xx >= 0) || (a <= 0 && xx <= 0)))
        can = bruteForce(xx != 0 ? xx * max(1LL, abs(a / xx) - 100) : xx, xx != 0 ? yy * max(1LL, abs(a / xx) - 100) : yy);
    }
    printf("%s\n", can ? "Yes" : "No");
  }

  return 0;
}