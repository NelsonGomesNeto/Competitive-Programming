#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int s(int n)
{
  int ans = 0;
  while (n)
  {
    ans += n % 10;
    n /= 10;
  }
  return ans;
}

int main()
{
  int a, b;
  while (~scanf("%d %d", &a, &b))
  {
    printf("%d\n", max(s(a), s(b)));
  }
  return 0;
}