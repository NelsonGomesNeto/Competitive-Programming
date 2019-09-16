#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN], minus1[maxN + 1];
lli accNeg[maxN + 1], accPos[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 0, t = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    if (a[i] < 0) t = 1 - t;
    accNeg[i + 1] = accNeg[i] + t;
    accPos[i + 1] = accPos[i] + (1 - t);
    minus1[i + 1] = minus1[i] + (a[i] < 0);
  }

  lli neg = 0, pos = 0;
  for (int i = 0, t = 0; i < n; i ++)
  {
    lli m = minus1[n] - minus1[i];
    // printf("%d %lld %d - %lld %lld\n", i, m, t, accNeg[n] - accNeg[i], accPos[n] - accPos[i]);
    if (!t)
      neg += accNeg[n] - accNeg[i], pos += accPos[n] - accPos[i];
    else
      neg += accPos[n] - accPos[i], pos += accNeg[n] - accNeg[i];
    if (a[i] < 0) t = 1 - t;
  }
  printf("%lld %lld\n", neg, pos);

  return(0);
}
// Fazer dois arrays de 0 e 1
// começa com 0, e muda para 1 quanto tem a[i] < 0; e volta para 0 quando tem outro...
// o outro array é o not desse