#include <bits/stdc++.h>
using namespace std;

const int maxX = 1e6;
bool composite[maxX + 1];
vector<int> primes;

int main()
{
  composite[0] = composite[1] = true;
  for (int i = 2; i <= maxX; ++i)
  {
    if (!composite[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxX; ++j)
    {
      composite[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  for (int i = 0; i < 1e2; i ++)
    printf("%d: %s\n", i, composite[i] ? "Not prime" : "Prime");
  return(0);
}
