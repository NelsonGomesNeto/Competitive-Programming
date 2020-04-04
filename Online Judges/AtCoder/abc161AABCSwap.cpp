#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, y, z;
  while (scanf("%d %d %d", &x, &y, &z) != EOF)
  {
    swap(x, y);
    swap(x, z);
    printf("%d %d %d\n", x, y, z);
  }
  return 0;
}