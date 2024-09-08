#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
int a[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int s = 0, d = 0;
    for (int i = 0, j = n - 1, turn = 1; i <= j; turn = !turn)
    {
      if (a[i] > a[j]) turn & 1 ? s += a[i++] : d += a[i++];
      else turn & 1 ? s += a[j--] : d += a[j--];
    }
    printf("%d %d\n", s, d);
  }
  return 0;
}