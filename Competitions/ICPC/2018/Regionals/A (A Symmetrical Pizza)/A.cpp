#include <bits/stdc++.h>
using namespace std;

int main()
{
  double R;
  while (scanf("%lf", &R) != EOF)
  {
    int r = round(R * 100), a = round(R * 100), count = 1, best = 0;
    while (r) r = (r + a) % 36000, count ++;
    printf("%d\n", count);
  }
  return(0);
}