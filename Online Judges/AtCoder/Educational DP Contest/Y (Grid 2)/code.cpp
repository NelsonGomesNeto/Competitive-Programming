#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int h, w, n;
struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
  bool operator==(const Pos &other) const { return i == other.i && j == other.j; }
  // bool operator<(const Pos &other) const { return i < other.i && (i == other.i && j < other.j); }
  bool operator<(const Pos &other) const { return i < other.i || (i == other.i && j < other.j); }
};
vector<Pos> walls;
lli ways[maxN];

/* choose(n, k) = n! / (k! * (n - k)!)
  cases where n is too large, but close to k:
    choose(n, k) = pi(k + 1 to n, i) / (n - k)!
  Pascal's Triangle:
    1      1      1      1      1 
    1      2      3      4      5 
    1      3      6     10
    1      4     10
    1      5
    1
    matrix(r, c) = choose(r + c, c)
    (0-indexed)
*/
const int maxX = 1e6 + 1;
const lli mod = 1e9 + 7; // could be two as well

lli fat[maxX], invFat[maxX];
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
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli choose(lli nn, lli kk)
{
  if (nn < kk) return 0;
  if (nn < mod) return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
  lli ans = 1;
  while (nn || kk)
  {
    lli nnn = nn % mod, kkk = kk % mod;
    nn /= mod, kk /= mod;
    ans = ans * choose(nnn, kkk) % mod;
  }
  return ans;
}

lli totalPaths(int i, int j)
{
  return choose(i + j, j);
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  while (scanf("%d %d %d", &h, &w, &n) != EOF)
  {
    walls.clear();
    walls.resize(n);
    for (int i = 0; i < n; i++)
      walls[i].read();
    sort(walls.begin(), walls.end());

    lli ans = totalPaths(h - 1, w - 1);
    for (int i = 0; i < n; i++)
    {
      Pos &wall = walls[i];
      lli toInvalid = totalPaths(wall.i, wall.j);
      DEBUG printf("\t\tstarting: %lld\n", toInvalid);
      for (int j = 0; j < i; j++)
      {
        Pos &blocking = walls[j];
        if (wall.i >= blocking.i && wall.j >= blocking.j)
        {
          lli fromWall = ways[j] * totalPaths(wall.i - blocking.i, wall.j - blocking.j);
          DEBUG printf("\t\t%d (%d, %d) - %lld\n", j, blocking.i, blocking.j, fromWall);
          toInvalid = (toInvalid - fromWall + mod) % mod;
        }
      }
      ways[i] = toInvalid;
      lli toEnd = totalPaths(h - 1 - wall.i, w - 1 - wall.j);
      DEBUG printf("\t%d (%d, %d) - %lld %lld\n", i, wall.i, wall.j, toInvalid, toEnd);
      ans = (ans - toInvalid * toEnd % mod + mod) % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}