#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxX = 1e6;
bool composite[maxX + 1];
int mi[maxX + 1];
vector<int> primes;

// TODO - Implement version for big numbers
int miFunc(lli number)
{
  if (number <= maxX) return mi[number];
  return 0xfff;
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

  for (int i = 1; i < 20; i ++)
    printf("%d - %d\n", i, mi[i]);
  return(0);
}
