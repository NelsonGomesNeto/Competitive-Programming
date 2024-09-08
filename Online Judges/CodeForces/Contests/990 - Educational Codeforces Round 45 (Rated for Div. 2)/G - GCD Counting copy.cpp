#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 2e5;
bool notPrime[maxX + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxX + 1];

lli phi(lli number)
{
  lli ans = 1;
  if (number <= maxX)
    for (auto &p: primeFactors[number])
    {
      if (number % p.first) continue;
      // ans *= (p - 1) * p^(e - 1)
      number /= p.first, ans *= p.first - 1;
      while (number % p.first == 0)
        number /= p.first, ans *= p.first;
    }
  else
    for (int i = 2, end = sqrt(number); number >= i && i <= end; i ++)
    {
      if (number % i) continue;
      // ans *= (p - 1) * p^(e - 1)
      number /= i, ans *= i - 1;
      while (number % i == 0)
        number /= i, ans *= i;
    }
  if (number > 1) ans *= number - 1;
  return(ans);
}

const int maxN = 2e5, maxA = 2e5; int n;
lli sumByDivisor[maxA + 1];
int a[maxN];
vector<int> tree[maxN];
vector<int> divisors[maxA + 1];
vector<int> verticesByDivisors[maxA + 1];

int parent[maxN];
void precalcParent(int u = 0, int prv = -1)
{
  for (int v : tree[u])
    if (v != prv)
    {
      parent[v] = u;
      precalcParent(v, u);
    }
}

vector<int> subtree[maxN];
int has[maxN];
int subtreeSize[maxN];
lli sumBelow[maxN], reRootedSum[maxN];
void calcSumBelow(int u)
{
  reRootedSum[u] = 0;
  sumBelow[u] = 0;
  subtreeSize[u] = 1;
  for (int v : subtree[u])
  {
    calcSumBelow(v);
    subtreeSize[u] += subtreeSize[v];
    sumBelow[u] += sumBelow[v] + (1 + subtreeSize[v]);
  }
}
void reRootSum(int root, int u)
{
  reRootedSum[u] += sumBelow[u];
  for (int v : subtree[u])
  {
    lli sumAbove = reRootedSum[u] - (sumBelow[v] + (1 + subtreeSize[v])) + (1 + subtreeSize[root] - subtreeSize[v]);
    reRootedSum[v] = sumAbove;
    reRootSum(root, v);
  }
}
lli sumSubtree(int u)
{
  lli sum = reRootedSum[u];
  for (int v : subtree[u])
    sum += sumSubtree(v);
  return sum;
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

  for (int i = 1; i <= maxA; ++i)
  {
    divisors[i].push_back(1);
    if (i > 1) divisors[i].push_back(i);
    for (int j = 2, end = sqrt(i); j <= end; ++j)
      if (i % j == 0)
      {
        divisors[i].push_back(j);
        int jj = i / j;
        if (jj != j && i % jj == 0)
          divisors[i].push_back(jj);
      }
  }

  int hehe = 0;
  while (~scanf("%d", &n))
  {
    if (hehe++) printf("-------------------\n");

    for (int i = 0; i <= maxA; ++i)
      verticesByDivisors[i].clear();

    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      tree[i].clear();
      for (int d : divisors[a[i]])
        verticesByDivisors[d].push_back(i);
    }

    for (int i = 1; i < n; ++i)
    {
      int u, v; scanf("%d %d", &u, &v); --u, --v;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    parent[0] = -1;
    precalcParent();

    memset(has, -1, sizeof(has));
    lli ans = 0;
    for (int d = 1; d <= maxA; ++d)
    {
      // if (verticesByDivisors[d].size() <= 1) continue;

      for (int u : verticesByDivisors[d])
        subtree[u].clear(), has[u] = d, sumBelow[u] = 0;

      vector<int> roots;
      for (int u : verticesByDivisors[d])
        if (u && has[parent[u]] == d)
          subtree[parent[u]].push_back(u);
        else
          roots.push_back(u);

      // lli allPathsSum = 0;
      lli sum = 0;
      for (int u : roots)
      {
        calcSumBelow(u);
        // reRootedSum[u] = 0;
        // reRootSum(u, u);
        lli nodes = subtreeSize[u];

        // allPathsSum = (allPathsSum + (sumSubtree(u) >> 1)) % mod;
        sum += nodes + (nodes * (nodes-1) / 2);
        if (d == 2) printf("\t\t%lld\n", nodes);
      }
      sumByDivisor[d] = sum;
      if (d == 2) printf("\t%d - %d - %lld\n", d, (int)verticesByDivisors[d].size(), sum);
      // ans = (ans + phi(d) * sum % mod) % mod;
    }

    for (int d = 1; d <= 6; ++d)
    {
      lli ans = sumByDivisor[d];
      // for (int dd : divisors[d])
      //   ans += phi(dd) * sumByDivisor[dd];
      printf("%d %lld\n", d, ans);
    }

  }
  return 0;
}