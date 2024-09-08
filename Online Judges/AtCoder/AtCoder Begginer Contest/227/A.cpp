#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, k, a;
  while (~scanf("%d %d %d", &n, &k, &a))
  {
    printf("%d\n", (a - 1 + k - 1) % n + 1);
  }
  return 0;
}