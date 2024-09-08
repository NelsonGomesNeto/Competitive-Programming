#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
int n;
char s[maxN + 1];
int x, y;

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", s);
    scanf("%d %d", &x, &y);
    swap(x, y);

    for (int i = 0; i < n; ++i)
    {
      switch (s[i])
      {
        case 'R':
          if (x > 0) --x;
          break;
        case 'L':
          if (x < 0) ++x;
          break;
        case 'D':
          if (y > 0) --y;
          break;
        case 'U':
          if (y < 0) ++y;
          break;
        default:
          assert(false);
          break;
      }
    }

    bool can = x == 0 && y == 0;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
