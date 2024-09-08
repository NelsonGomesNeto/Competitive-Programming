#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 64;
int a[maxN];

int main()
{
  for (int i = 0; i < maxN; ++i)
    scanf("%d", &a[i]);

  unsigned long long int ans = 0;
  for (int i = 0; i < maxN; ++i)
    ans |= (a[i] * 1ULL) << i;
  printf("%llu\n", ans);
  return 0;
}
