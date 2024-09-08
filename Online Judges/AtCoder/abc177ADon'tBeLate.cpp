#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int d, t, s;
  while (scanf("%d %d %d", &d, &t, &s) != EOF)
  {
    printf("%s\n", d / s + (d % s != 0) <= t ? "Yes" : "No");
  }
  return 0;
}