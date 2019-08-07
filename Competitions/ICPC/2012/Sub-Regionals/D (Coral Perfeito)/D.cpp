#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4; int n;
int a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    int mean = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      mean += a[i];
    }
    mean /= n;

    int up = 0, down = 0;
    for (int i = 0; i < n; i ++)
      if (a[i] > mean) down += a[i] - mean;
      else up += mean - a[i];

    printf("%d\n", up == down ? up + 1 : -1);
  }
  return(0);
}