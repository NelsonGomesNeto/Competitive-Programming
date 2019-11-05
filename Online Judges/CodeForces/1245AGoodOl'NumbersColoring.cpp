#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int a, b; scanf("%d %d", &a, &b);
    printf("%s\n", gcd(a, b) == 1 ? "Finite" : "Infinite");
  }
  return 0;
}
