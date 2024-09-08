#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    int rem = n % 10;
    printf("%s\n", rem == 3 ? "bon" : (rem == 0 || rem == 1 || rem == 6 || rem == 8 ? "pon" : "hon"));
  }
  return 0;
}