#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n, k;
lli a[maxN];

bool notPrime[maxN];
vector<int> primes;

vector<pair<int, int>> primeFactorization(lli num)
{
  vector<pair<int, int>> primeFactors;
  lli end = sqrt(num);
  for (lli i: primes)
  {
    if (i > end) break;
    if (num % i == 0)
    {
      int p = 0;
      while (num % i == 0) num /= i, p ++;
      primeFactors.push_back({i, p});
    }
  }
  if (num != 1)
    primeFactors.push_back({num, 1});
  return primeFactors;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxN; i ++)
  {
    primes.push_back(i);
    for (int j = 0; i*primes[j] < maxN; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &a[i]);

  map<vector<pair<int, int>>, int> cnt;
  lli ans = 0;
  for (int i = 0; i < n; i ++)
  {
    vector<pair<int, int>> pf = primeFactorization(a[i]);
    vector<pair<int, int>> aa, bb;
    DEBUG {
      printf("%lld: ", a[i]);
      for (auto &p: pf) printf("%lld^%d", p.first, p.second);
      printf("\n");
    }
    for (auto &p: pf)
    {
      if (p.second % k == 0) continue;
      aa.push_back({p.first, p.second % k});
      bb.push_back({p.first, k - p.second % k});
    }
    ans += cnt[bb];
    if (!cnt.count(aa)) cnt[aa] = 0;
    cnt[aa] ++;
  }
  printf("%lld\n", ans);

  return 0;
}
