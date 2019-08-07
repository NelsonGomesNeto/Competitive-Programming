#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int isPrime[1000001];

void buildSieve()
{
  for (int i = 0; i <= 1000000; i ++) isPrime[i] = 1;
  isPrime[0] = isPrime[1] = 0; isPrime[2] = 1;
  for (int i = 2; i <= 1000; i ++)
    for (int j = 2; j * i <= 1000000; j ++)
      isPrime[i*j] = 0;
}

int main()
{
  buildSieve();
  // for (int i = 0; i < 100; i ++)
  //   printf("%d - %s\n", i, isPrime[i] ? "Prime" : "Not Prime");

  int n; scanf("%d", &n);
  while (n --)
  {
    lli x; scanf("%lld", &x);

    double rEnd = sqrt(x); lli end = rEnd;
    int can = 1;
    if (rEnd == end && x != 1) can = isPrime[end];
    else can = 0;

    printf("%s\n", can ? "YES" : "NO");
  }
  return(0);
}