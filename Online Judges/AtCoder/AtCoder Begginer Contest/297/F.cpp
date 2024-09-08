#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Editorial

BB = bounding box
f(h, w) = # ways to make a BB with height `h` and width `w`.
positions(h, w) = (n - h + 1) * (m - w + 1) # all possible positions for that BB
area(h, w) = h * w // area of that BB
invChooseK = product(j = [0 : k); 1 / (area(n, m) - j)) // probability of choosing all cells

Expected score = sum(every h, w; area(h, w) * f(h, w) * k! * invChooseK)

That's it! But calculating f(h, w) is not trivial.
That can be done with Inclusion Exclusion:

g(h, w) = choose(area(h, w), k)
The BB is defined by all four sides.
So, for each side: we choose to remove it or not.

f(h, w) = {
  for every side combination (2^4):
    ans += (-1)^|numberOfSides| * g(h - deltaH(removedSides), w - deltaW(removedSides))
}

Quick example:
f(2, 3) = g(2, 3)
But that includes the BB [(0, 1), (1, 2)] (which is missing the left side)
f(2, 3) = g(2, 3) - g(2, 2)
Similarly, this includes a BB missing the right side
f(2, 3) = g(2, 3) - g(2, 2) - g(2, 2)
But now we're removing the BB [(0, 1), (1, 1)]
f(2, 3) = g(2, 3) - 2*g(2, 2) + g(2, 1)
Awesome! That's how Inclusion Exclusion will handle everything.

*/

/*
left = 1 << 0,
top = 1 << 1,
right = 1 << 2,
bottom = 1 << 3
*/
char lol[5] = "LTRB";
string bin(int num)
{
  string ans = "";
  int i = 0;
  while (num)
  {
    if (num & 1)
      ans.push_back(lol[i]);
    num >>= 1;
    ++i;
  }
  return ans;
}

const int maxX = 1e6 + 1;
lli fat[maxX], invFat[maxX];
const lli mod = 998244353LL;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL)
      ans = ans * x % mod;
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
  if (nn < kk)
    return 0;
  if (nn < mod)
    return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
  lli ans = 1;
  while (nn || kk)
  {
    lli nnn = nn % mod, kkk = kk % mod;
    nn /= mod, kk /= mod;
    ans = ans * choose(nnn, kkk) % mod;
  }
  return ans;
}

const int maxNM = 1e6;
const int maxN = 1e3;
int n, m, k;
lli totalArea, invTotalArea;

enum side {
  left = 1 << 0,
  top = 1 << 1,
  right = 1 << 2,
  bottom = 1 << 3
};
bool hasSides(const int mask, const int s)
{
  return (mask & s) == s;
}
const vector<side> sides = {side::top, side::bottom, side::left, side::right};
int getHd(const int mask) { return (int)hasSides(mask, side::top) + hasSides(mask, side::bottom); }
int getWd(const int mask) { return (int)hasSides(mask, side::left) + hasSides(mask, side::right); }
lli piu(const int h, const int w, int mask = 0, int i = 0, int setSize = 0)
{
  if (i == sides.size())
  {
    lli res = choose(max(0, (h - getHd(mask)))*max(0, (w - getWd(mask))), k);
    return setSize & 1 ? mod - res : res;
  }

  lli ans = piu(h, w, mask, i + 1, setSize);
  ans = (ans + piu(h, w, mask | sides[i], i + 1, setSize + 1)) % mod;

  return ans;
}

bool visited[maxN][maxN];
lli cnt[maxN][maxN];
lli oracleSolve(int j = 0, int minX = maxN + 1, int maxX = -1, int minY = maxN + 1, int maxY = -1)
{
  if (j == k)
  {
    ++cnt[maxX - minX + 1][maxY - minY + 1];
    return (maxX - minX + 1) * (maxY - minY + 1) % mod;
  }

  lli ans = 0;
  for (int y = 1; y <= n; ++y)
    for (int x = 1; x <= m; ++x)
      if (!visited[y][x])
      {
        visited[y][x] = true;
        ans = (ans + oracleSolve(j + 1, min(minX, x), max(maxX, x), min(minY, y), max(maxY, y)) * inv(n * m - j)) % mod;
        visited[y][x] = false;
      }
  return ans;
}
lli oracle()
{
  memset(cnt, 0, sizeof(cnt));
  memset(visited, false, sizeof(visited));
  return oracleSolve();
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  while (~scanf("%d %d %d", &n, &m, &k))
  {
    // if (n > 10) break;
    totalArea = n * m;
    lli invChooseK = 1;
    for (int j = 0; j < k; ++j)
      invChooseK = invChooseK * inv(totalArea - j) % mod;

    lli ans = k == 1 ? 1 : 0;
    // lli oracleAns = oracle();
    if (k > 1)
      for (int h = 1; h <= n; ++h)
        for (int w = 1; w <= m; ++w)
        {
          const lli area = h * w;
          if (area < k) continue;
          const lli positions = (lli)(m - w + 1) * (n - h + 1) % mod;

          lli ways = piu(h, w) * fat[k] % mod;
          // printf("\t%d %d | %lld | %lld %lld\n", h, w, ways, cnt[w][h] / positions / fat[k], cnt[w][h] / positions);
          const lli p = ways * invChooseK % mod;

          ans = (ans + area * p % mod * positions % mod) % mod;
        }
    // printf("n: %d m: %d k: %d | ans: %lld | oracle: %lld\n", n, m, k, ans, oracleAns);
    // fflush(stdout);
    // assert(ans == oracleAns);
    printf("%lld\n", ans);
  }
  return 0;
}
