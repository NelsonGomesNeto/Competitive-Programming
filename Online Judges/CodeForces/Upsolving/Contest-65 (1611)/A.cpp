#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n;
vector<int> digits;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    digits.clear();
    int aux = n;
    while (aux)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }

    int ans = -1;
    for (int d: digits) if (~d & 1) ans = 2;
    if (~digits.back() & 1) ans = 1;
    if (~digits[0] & 1) ans = 0;
    printf("%d\n", ans);
  }
  return 0;
}
