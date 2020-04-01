#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  printf("%d\n", (n >> 1) + (n & 1));
  return 0;
}