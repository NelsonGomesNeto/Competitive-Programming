#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  double angle;
  while (~scanf("%lf", &angle))
  {
    lli total = angle * 1000000;
    lli h = total * 24 / 360 / 1000000;
    lli m = total * (24 * 60) / 360 / 1000000 % 60;
    lli s = total * 24 * 60 * 60 / 360 / 1000000 % 60;

    h = (h + 6) % 24;

    if (angle < 90) printf("Bom Dia!!\n");
    else if (angle < 180) printf("Boa Tarde!!\n");
    else if (angle < 270) printf("Boa Noite!!\n");
    else printf("De Madrugada!!\n");

    printf("%02lld:%02lld:%02lld\n", h, m, s);
  }
  return 0;
}