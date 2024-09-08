#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int k, a, b;
  while (scanf("%d %d %d", &k, &a, &b) != EOF)
  {
    bool can = false;
    for (int i = 1; i*k <= b; i++)
      if (i*k >= a)
        can = true;
    printf("%s\n", can ? "OK" : "NG");
  }
  return 0;
}