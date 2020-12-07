#include <bits/stdc++.h>
#define lli long long int

int perfect(int n)
{
  int sum = 0;
  while (n)
  {
    sum += n % 10;
    n /= 10;
  }
  return(sum == 10);
}

int main()
{
  int n; scanf("%d", &n); n --;
  lli pn = 19;
  while (n --)
  {
    pn += 9;
    while (!perfect(pn)) pn ++;
  }
  printf("%lld\n", pn);
  return(0);
}
