#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e6; int n, k;
lli h[maxN], acc[maxN + 1];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++) scanf("%lld", &h[i]);
    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + h[i];

    int ansI = 0; lli ansV = maxN*k;
    for (int i = 0; i + k - 1 < n; i++)
    {
      lli curr = acc[i + k] - acc[i];
      if (curr < ansV)
        ansV = curr, ansI = i + 1;
    }
    printf("%d\n", ansI);
  }
  return 0;
}