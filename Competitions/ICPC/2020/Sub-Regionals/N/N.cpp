#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 31622777; // sqrt(10^15)
bool notPrime[maxX + 1];
vector<int> primes;

const int maxN = 1e3; int m, n, k;
lli ns[maxN], ms[maxN];
vector<pair<lli, int>> nToM[maxN], mToN[maxN];

void propagate(int i)
{
  for (auto &e: mToN[i])
    ns[e.first] /= ms[i];
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i); //primeFactors[i].push_back({i, 1});
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      // primeFactors[i * primes[j]].push_back({primes[j], p});
      // primeFactors[i * primes[j]].insert(primeFactors[i * primes[j]].end(), primeFactors[num].begin(), primeFactors[num].end());
      if (i % primes[j] == 0) break;
    }
  }

  while (scanf("%d %d %d", &m, &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &ns[i]);

    for (int i = 0; i < k; i++)
    {
      int mi, ni, d; scanf("%d %d %d", &mi, &ni, &d); mi--, ni--;
      nToM[ni].push_back({mi, d});
      mToN[mi].push_back({ni, d});
    }

    int sp = 0;
    for (int i = 0; i < m; i++)
    {
      ms[i] = -1;
      for (; sp < primes.size(); sp++)
        if (ns[mToN[i][0].first] % primes[sp] == 0)
        {
          ms[i] = primes[sp++];
          propagate(i);
          break;
        }

      if (ms[i] == -1)
      {
        ms[i] = ns[mToN[i][0].first];
        propagate(i);
      }
    }

    for (int i = 0; i < m; i++)
      printf("%lld%c", ms[i], i < m - 1 ? ' ' : '\n');
  }
  return 0;
}