#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6;
bool notPrime[maxN];
vector<int> primes;

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxN; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  for (int i = 0; i < 1e2; i ++)
    printf("%d: %s\n", i, notPrime[i] ? "Not prime" : "Prime");
  return(0);
}
