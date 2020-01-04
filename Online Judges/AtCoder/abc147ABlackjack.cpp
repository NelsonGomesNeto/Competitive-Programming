#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a[3];
bool read()
{
  for (int i = 0; i < 3; i ++)
    if (scanf("%d", &a[i]) == EOF)
      return false;
  return true;
}

int main()
{
  while (read())
  {
    int s = 0;
    for (int i = 0; i < 3; i ++)
      s += a[i];
    printf("%s\n", s >= 22 ? "bust" : "win");
  }
  return 0;
}