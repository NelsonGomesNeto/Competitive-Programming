#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
bool has[11][11];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(has, false, sizeof(has));
    bool can = true;
    for (int i = 0; i < n; i++)
    {
      int d, l, r, c; scanf("%d %d %d %d", &d, &l, &r, &c);
      if (d == 0) // horizontal
      {
        can &= c + l - 1 <= 10;
        for (int j = c; j <= c + l - 1 && j <= 10; j++)
        {
          if (has[r][j])
            can = false;
          has[r][j] = true;
        }
      }
      else
      {
        can &= r + l - 1 <= 10;
        for (int ii = r; ii <= r + l - 1 && ii <= 10; ii++)
        {
          if (has[ii][c])
            can = false;
          has[ii][c] = true;
        }
      }
    }
    printf("%s\n", can ? "Y" : "N");
  }
  return 0;
}
