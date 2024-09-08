#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n = 8;
  int a[n];
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  bool valid = true;
  for (int i = 0; i < n; ++i)
  {
    if (i && a[i] < a[i - 1]) valid = false;
    if (a[i] < 100 || a[i] > 675) valid = false;
    if (a[i] % 25 != 0) valid = false;
  }
  printf("%s\n", valid ? "Yes" : "No");
  return 0;
}
