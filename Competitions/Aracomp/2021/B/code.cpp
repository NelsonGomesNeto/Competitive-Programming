#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (~scanf("%d %d", &a, &b))
  {
    if (b <= 2) printf("nova\n");
    else if (b >= 97) printf("cheia\n");
    else if (a > b) printf("minguante\n");
    else printf("crescente\n");
  }
  return 0;
}