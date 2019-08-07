#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli n; scanf("%lld", &n);
  int prime = 1;
  for (int i = 2; i <= sqrt(n); i ++)
    if (n % i == 0) prime = 0;

  printf("%s\n", (prime && n != 1) ? "sim" : "nao");

  return(0);
}