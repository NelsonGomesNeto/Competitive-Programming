#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (~scanf("%d %d", &a, &b))
  {
    a--, b--;
    printf("%s\n", (a + 1) % 10 == b || (b + 1) % 10 == a ? "Yes" : "No");
  }
  return 0;
}