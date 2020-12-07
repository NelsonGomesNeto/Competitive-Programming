#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1 - 10 do manually

n odd and n / 2 even:
  exactly pascal's triangle (line n / 2)
n even and n / 2 odd:
  exactly pascal's triangle, but i will be i / 2 on pascal's triangle (line n / 2 - 1)
n odd and n / 2 odd:
  get(n - 1) answer
  1 abs(a[0] + a[1]) abs(a[1] - a[2]) abs(a[2] + a[3]) ...
  but from mid to end: alternativelly flip the signs
n even and n / 2 even:
  exactly pascal's triangle (line n / 2), but i will be i / 2 and alternativelly flip the signs

*/

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7;
lli a[maxN];

lli fact[maxN + 1], invFact[maxN + 1];
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
lli modInv(lli x)
{
  return modPow(x, mod - 2);
}
lli choose(lli n, lli k)
{
  return fact[n] * invFact[n - k] % mod * invFact[k] % mod;
}
lli pascal(int row, int column)
{
  return choose(row, column);
}

vector<lli> getMultiples()
{
  vector<lli> multiples;
  bool nOdd = n & 1, nd2Odd = (n >> 1) & 1;
  if (nOdd && !nd2Odd)
  {
    multiples.resize(n);
    int line = n >> 1;
    for (int i = 0; i < multiples.size(); i++)
      multiples[i] = (i & 1) ? 0 : pascal(line, i >> 1);
  }
  else if (!nOdd && nd2Odd)
  {
    multiples.resize(n);
    int line = (n >> 1) - 1;
    for (int i = 0; i < multiples.size(); i++)
      multiples[i] = pascal(line, i >> 1);
  }
  else if (nOdd && nd2Odd)
  {
    n--;
    vector<lli> aux = getMultiples();
    n++;
    multiples.push_back(1);
    for (int i = 0, turn = 0; i < aux.size() - 1; i++, turn = !turn)
      multiples.push_back(((aux[i] + (turn ? -aux[i + 1] : aux[i + 1])) % mod + mod) % mod);
    for (int i = 1, turn = 0; i < multiples.size(); i++, turn = !turn)
      multiples[i] = ((turn ? -multiples[i] : multiples[i]) + mod) % mod;
    multiples.push_back(-1 + mod);
  }
  else if (!nOdd && !nd2Odd)
  {
    multiples.resize(n);
    int line = (n >> 1) - 1;
    for (int i = 0, turn = 0; i < multiples.size(); i++, turn = !turn)
      multiples[i] = ((turn ? -pascal(line, i >> 1) : pascal(line, i >> 1)) + mod) % mod;
  }
  return multiples;
}

int main()
{
  fact[0] = 1, invFact[0] = modInv(1);
  for (lli i = 1; i <= maxN; i++)
  {
    fact[i] = i * fact[i - 1] % mod;
    invFact[i] = modInv(fact[i]);
  }

  int t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t++) printf("-----------------------\n");
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    vector<lli> multiples = getMultiples();
    DEBUG for (int i = 0; i < multiples.size(); i++) printf("%lld%c", multiples[i], i < multiples.size() - 1 ? ' ' : '\n');
    lli ans = 0;
    for (int i = 0; i < multiples.size(); i++)
      ans = (ans + a[i] * multiples[i] % mod + mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}