#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a[3]; scanf("%d %d %d", &a[0], &a[1], &a[2]);
  sort(a, a+3);
  printf("%d\n", a[1] + a[2]);
  return 0;
}