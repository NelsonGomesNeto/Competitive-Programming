#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
int a[maxN], c[maxN];

const int maxX = 1e4;
bool notPrime[maxX + 1];
vector<int> groups[maxX + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxX + 1];

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

  int t; scanf("%d", &t);
  while (t--)
  {
    for (int i: primes) groups[i].clear();

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      vector<pair<lli, int>> pf = getPrimeFactors(a[i]);
      groups[pf.begin()->first].push_back(i);
    }

    int m = 0;
    set<int> used;
    for (int i: primes)
    {
      bool done = false;
      for (int j: groups[i])
      {
        done = true;
        c[j] = m + 1;
      }
      if (done)
      {
        used.insert(m + 1);
        m = (m + 1) % 11;
      }
    }
    printf("%d\n", (int)used.size());
    for (int i = 0; i < n; i++)
      printf("%d%c", c[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
