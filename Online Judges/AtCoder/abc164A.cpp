#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int s, w;
  while (scanf("%d %d", &s, &w) != EOF)
    printf("%s\n", w >= s ? "unsafe" : "safe");
  return 0;
}