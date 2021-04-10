#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e7;

int c;
const int maxC = 1e7;
int ans[maxC + 1];

const int maxX = 5e7;
bool notPrime[maxX + 1];
vector<int> primes;
int d[maxX + 1];

int main()
{
  for (int i = 1; i <= maxX; i ++)
    d[i] = 1;

  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), d[i] *= (i + 1);
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      int toAdd = 1, mul = 1;
      while (num % primes[j] == 0)
      {
        num /= primes[j], p++;
        mul *= primes[j];
        toAdd += mul;
      }
      d[i * primes[j]] *= toAdd;
      d[i * primes[j]] *= d[num];
      if (i % primes[j] == 0) break;
    }
  }

  memset(ans, -1, sizeof(ans));
  for (int i = 1; i <= maxN; i++)
  {
    int n = i;
    int dd = d[i];
    DEBUG
      if (i < 20)
        printf("%d %d\n", i, d[i]);
    if (dd <= maxC && ans[dd] == -1)
      ans[dd] = i;
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &c);
    DEBUG printf("%d - %d\n", c, ans[c]);
    else printf("%d\n", ans[c]);
  }
  return 0;
}