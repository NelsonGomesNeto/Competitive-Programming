#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a[5];
  for (int i = 0; i < 5; i++) scanf("%d", &a[i]);
  for (int i = 0; i < 5; i++) { if (a[i] == 0) { printf("%d\n", i + 1); break; } }
  return 0;
}