#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const string pi = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";

int main()
{
  int n;
  while (~scanf("%d", &n)) {
    printf("%s\n", pi.substr(0, n + 2).c_str());
  }
  return 0;
}
