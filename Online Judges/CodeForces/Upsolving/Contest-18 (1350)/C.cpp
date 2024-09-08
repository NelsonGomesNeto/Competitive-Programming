#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

const int maxX = 2e5 + 1;
bool notPrime[maxX + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxX + 1];
int cnt[maxX][20];

vector<pair<lli, int>> getPrimeFactors(lli num)
{
  if (num <= maxX) return primeFactors[num];
  vector<pair<lli, int>> pf;
  for (lli i: primes)
  {
    if (i > num) break;
    if (num % i == 0)
    {
      int p = 0;
      while (num % i == 0) num /= i, p ++;
      pf.push_back({i, p});
    }
  }
  if (num != 1)
    pf.push_back({num, 1});
  return pf;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), primeFactors[i].push_back({i, 1});
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      primeFactors[i * primes[j]].push_back({primes[j], p});
      primeFactors[i * primes[j]].insert(primeFactors[i * primes[j]].end(), primeFactors[num].begin(), primeFactors[num].end());
      if (i % primes[j] == 0) break;
    }
  }

  while (scanf("%d", &n) != EOF)
  {
    set<int> nums;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      nums.insert(a[i]);
    }
    // vector<int> lol;
    // for (int i: nums) lol.push_back(i);
    // for (int i = 0; i < lol.size(); i++) a[i] = lol[i];
    // n = lol.size();

    for (int i = 0; i < primes.size(); i++)
      for (int j = 0; j < 20; j++)
        cnt[primes[i]][j] = 0;

    for (int i = 0; i < n; i++)
    {
      vector<pair<lli, int>> pf = getPrimeFactors(a[i]);
      for (auto &p: pf)
        cnt[p.first][p.second]++;
    }
    for (int i = 0; i < primes.size(); i++)
    {
      int acc = 0;
      for (int j = 20 - 1; j >= 0; j--)
      {
        int aux = cnt[primes[i]][j];
        cnt[primes[i]][j] += acc;
        acc += aux;
      }
    }
    DEBUG printf("new n: %d\n", n);

    lli ans = 1;
    for (int i = 0; i < primes.size(); i++)
    {
      int curr = 0;
      for (int j = 0; j < 20; j++)
        if (cnt[primes[i]][j] >= max(1, n - 1))
          curr = j;
      lli hehe = 1;
      while (curr--) hehe *= (lli)primes[i];
      ans *= hehe;
    }
    DEBUG {
      vector<lli> aa;
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
          aa.push_back(lcm(a[i], a[j]));
      lli brute = aa.empty() ? a[0] : aa[0];
      for (int i = 1; i < aa.size(); i++)
        brute = gcd(brute, aa[i]);
      printf("\t%lld - %lld\n", brute, ans);
      if (brute != ans)
      {
        printf("NOT OK\n");
        for (int i = 0; i < n; i++)
          printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
      }
    }

    printf("%lld\n", ans);
  }
  return 0;
}
