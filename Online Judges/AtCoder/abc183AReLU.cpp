#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int relu(int x)
{
  return x >= 0 ? x : 0;
}

int main()
{
  int x;
  while (scanf("%d", &x) != EOF)
    printf("%d\n", relu(x));
  return 0;
}