#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli V, A; scanf("%lld %lld", &V, &A);
  lli b = 1, h = V;
  while (b*b*h != V || 4*b*h + 2*b*b != A)
  {
    b ++;
    h = V / (b*b);
  }
  printf("%lld %lld\n", b, h);
  return(0);
}