#include <bits/stdc++.h>
#define lli long long int
using namespace std;
bool isPrime[(int) 1e6 + 1];
vector<int> primes;
vector<lli> divisors;

int isPrimeFunc(lli num)
{
  lli end = sqrt(num);
  for (int i = 2; i <= end; i ++)
    if (num % i == 0) return(0);
  return(1);
}

int dispojed(lli num)
{
  if ((num <= 1e6 && isPrime[num]) || isPrimeFunc(num)) return(0);
  for (int i = 0; i < primes.size() && primes[i] < num; i ++)
    if (num % primes[i] == 0 && num / primes[i] && ((num / primes[i]) % primes[i]) == 0)
      return(0);
  return(1);
}

int main()
{
  memset(isPrime, true, sizeof(isPrime));
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i <= 1e6; i ++)
    for (int j = 2; i * j <= 1e6; j ++)
      isPrime[i * j] = false;
  for (int i = 0; i <= 1e6; i ++)
    if (isPrime[i]) primes.push_back(i);

  lli n; scanf("%lld", &n);
  lli end = sqrt(n);
  for (int i = 2; i <= end; i ++)
    if (n % i == 0)
    {
      divisors.push_back(i);
      if (n / i != i) divisors.push_back(n / i);
    }
  divisors.push_back(n);

  int ans = 0;
  for (int i = 0; i < divisors.size(); i ++)
    ans += dispojed(divisors[i]);

  printf("%d\n", ans);
  return(0);
}