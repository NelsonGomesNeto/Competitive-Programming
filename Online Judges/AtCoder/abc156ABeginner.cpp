#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, r;
  while (scanf("%d %d", &n, &r) != EOF)
  {
    printf("%d\n", n >= 10 ? r : r + 100 * (10 - n));
  }
  return 0;
}