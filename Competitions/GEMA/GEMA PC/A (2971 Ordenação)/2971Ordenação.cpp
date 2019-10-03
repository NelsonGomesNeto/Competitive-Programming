#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5; int n;
int a[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);
  sort(a, a+n);

  for (int i = 0; i < n; i ++)
    printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');

  return 0;
}