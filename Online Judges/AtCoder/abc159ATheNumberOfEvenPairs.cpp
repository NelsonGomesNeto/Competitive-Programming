#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    printf("%d\n", m*(m-1)/2 + n*(n-1)/2);
  }
  return 0;
}