#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  printf("%s\n", n < 4 || (n & 1) ? "NO" : "YES");
  return 0;
}