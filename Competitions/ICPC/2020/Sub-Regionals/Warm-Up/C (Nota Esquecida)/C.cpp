#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, m;
  while (scanf("%d %d", &a, &m) != EOF)
  {
    // m = (a + b) / 2
    // 2*m - a = b
    int b = 2*m - a;
    printf("%d\n", b);
  }
  return 0;
}