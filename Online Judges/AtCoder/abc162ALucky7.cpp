#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    bool has = false;
    while (n)
    {
      has |= n % 10 == 7;
      n /= 10;
    }
    printf("%s\n", has ? "Yes" : "No");
  }
  return 0;
}