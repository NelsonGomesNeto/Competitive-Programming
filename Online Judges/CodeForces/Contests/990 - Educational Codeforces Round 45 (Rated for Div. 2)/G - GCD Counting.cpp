#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6;
bool composite[maxX + 1];
int mi[maxX + 1];
vector<int> primes;

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
int subtreeSize(int u)
{
  int ans = 1;
  for (int v : subtree[u])
    ans += subtreeSize(v);
  return ans;
}

int main()
{
  composite[0] = composite[1] = true;
  mi[1] = 1;
  for (int i = 2; i <= maxX; ++i)
  {
    if (!composite[i])
    {
      primes.push_back(i);
      mi[i] = -1;
    }
    for (int j = 0; i*primes[j] <= maxX; ++j)
    {
      composite[i*primes[j]] = true;
      if (i % primes[j] == 0)
      {
        mi[i * primes[j]] = 0;
        break;
      }
      else
        mi[i * primes[j]] = mi[i] * mi[primes[j]];
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

    lli ans = 0;
    memset(has, -1, sizeof(has));
    for (int d = 1; d <= maxA; ++d)
    {
      for (int u : verticesByDivisors[d])
        subtree[u].clear(), has[u] = d;

      vector<int> roots;
      for (int u : verticesByDivisors[d])
        if (u && has[parent[u]] == d)
          subtree[parent[u]].push_back(u);
        else
          roots.push_back(u);

      lli sum = 0;
      for (int u : roots)
      {
        lli nodes = subtreeSize(u);
        sum += nodes * (nodes + 1) >> 1;
      }
      sumByDivisor[d] = sum;
    }

    for (int d = 1; d <= maxA; ++d)
    {
      lli ans = 0;
      for (int i = 1, end = maxA / d; i <= end; ++i)
      {
        // if (d == 1 && i <= 4) printf("\t%lld\n", sumByDivisor[d * i]);
        ans += mi[i] * sumByDivisor[d * i];
      }
      if (ans)
        printf("%d %lld\n", d, ans);
    }

    break;
  }
  return 0;
}