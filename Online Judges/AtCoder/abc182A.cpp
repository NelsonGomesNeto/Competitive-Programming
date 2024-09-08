#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (scanf("%d %d", &a, &b) != EOF)
  {
    int ans = 2*a + 100 - b;
    printf("%d\n", ans);
  }
  return 0;
}