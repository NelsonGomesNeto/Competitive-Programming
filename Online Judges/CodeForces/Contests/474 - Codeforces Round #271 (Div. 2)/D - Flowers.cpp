#include <bits/stdc++.h>
#define DEBUG if(0)

long long int mod = (long long int) 1e9 + 7;
long long int way[(int) 1e5 + 1];

int fillWays(int size, int k)
{
  if (size < 0) return(0);
  if (!size) return(1);
  if (way[size] == -1)
    way[size] = (fillWays(size - k, k) + fillWays(size - 1, k)) % mod;
  return(way[size]);
}

long long int module(long long int num)
{
  long long int ret = (num % mod);
  return(ret < 0 ? ret + mod : ret);
}

int main()
{
  memset(way, -1, sizeof(way));
  int tests, k; scanf("%d %d", &tests, &k);
  fillWays((int) 1e5, k);

  long long int acc[(int) 1e5 + 1]; acc[0] = 0;
  for (int i = 1; i <= 1e5; i ++)
    acc[i] = (way[i] + acc[i - 1]) % mod;

  while (tests -- > 0)
  {
    int a, b; scanf("%d %d", &a, &b);
    DEBUG for (int i = 1; i <= 1e5; i ++) printf("%d -> %lld\n", i, acc[i]);

    printf("%lld\n", module(acc[b] - acc[a - 1]));
  }

  return(0);
}