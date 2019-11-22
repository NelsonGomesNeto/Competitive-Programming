#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Draw a table, a the possible movements
  Notice that a pascal's triagle is formed, and it's rows happens every third-th
  diagonal in the table. So we just need to map the coordinates to the
  respective row and column in the the pascal's triangle.

  if ((x + y) % 3 != 0)
    isn't possible since all valid movements are on third-th diagonals
  
  line = (x + y) / 3
  column = x - line or y - line
  if (column < 0) also not possible
  Pascal's Triangle(line, column) = choose(line, column)
*/

const int maxN = 2e6 + 1;
const lli mod = 1e9 + 7;
lli fat[maxN];
lli x, y;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}

lli inv(lli num)
{
  return modPow(num, mod - 2);
}

lli choose(lli n, lli k)
{
  return fat[n] * inv(fat[k] * fat[n - k] % mod) % mod;
}

int main()
{
  fat[0] = 1;
  for (int i = 1; i < maxN; i ++)
    fat[i] = i * fat[i - 1] % mod;

  while (scanf("%lld %lld", &x, &y) != EOF)
  {
    if ((x + y) % 3 != 0) printf("0\n");
    else
    {
      lli line = (x + y) / 3;
      if (x - line < 0 || y - line < 0) printf("0\n");
      else printf("%lld\n", choose(line, x - line));
    }
  }
  return 0;
}