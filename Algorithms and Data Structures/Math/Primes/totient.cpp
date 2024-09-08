#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Euler's Totient function
  also known as Euler's Phi function

  phi(n) = integers [1, n] that are coprime with n
  phi(n) = gcd(i, n) == 1 for all i in [1, n]
*/

const int maxX = 1e7;
bool composite[maxX + 1];
int phi[maxX + 1];
vector<int> primes;

lli phiFunc(lli number)
{
  if (number <= maxX) return phi[number];
  lli ans = 1;
  for (int i = 2, end = sqrt(number); number >= i && i <= end; ++i)
  {
    if (number % i) continue;
    // ans *= (p - 1) * p^(e - 1)
    number /= i, ans *= i - 1;
    while (number % i == 0)
      number /= i, ans *= i;
  }
  if (number > 1) ans *= number - 1;
  return ans;
}

int main()
{
  composite[0] = composite[1] = true;
  phi[1] = 1;
  for (int i = 2; i <= maxX; ++i)
  {
    if (!composite[i])
    {
      primes.push_back(i);
      phi[i] = i - 1;
    }
    for (int j = 0; i*primes[j] <= maxX; ++j)
    {
      composite[i*primes[j]] = true;
      if (i % primes[j] == 0)
      {
        phi[i * primes[j]] = phi[i] * primes[j];
        break;
      }
      else
        phi[i * primes[j]] = phi[i] * phi[primes[j]];
    }
  }

  lli num;
  while (scanf("%lld", &num) != EOF)
    printf("phi(%lld) = %d\n", num, phi[num]);

  return 0;
}