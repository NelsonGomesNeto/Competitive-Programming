#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    bool yes = n == 1 || n > 4;
    printf("%s\n", yes ? "Yes" : "No");
  }
  return 0;
}