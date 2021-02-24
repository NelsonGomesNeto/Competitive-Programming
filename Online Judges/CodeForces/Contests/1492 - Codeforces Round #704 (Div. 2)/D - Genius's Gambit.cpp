#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, b, k;
int n;
string x, y;

int main()
{
  while (~scanf("%d %d %d", &a, &b, &k))
  {
    n = a + b;

    x = "";
    for (int i = 0; i < b; i++) x += "1";
    for (int i = 0; i < a; i++) x += "0";

    y = x;

    bool valid = k <= a + b - 2 || k == 0;
    if (k)
    {
      if (b - 1 + min(k, a) < n && b > 1)
      {
        y[b - 1] = '0';
        y[b - 1 + min(k, a)] = '1';

        if (k > a)
        {
          int rem = k - a;
          if (b - 2 - rem + 1 >= 0)
            y[b - 2 - rem + 1] = '0';
          y[b - 1] = '1';
        }
      }
      else
        valid = false;

      int ones = 0, zeros = 0;
      for (int i = 0; i < n; i++)
        if (x[i] == '1')
          ones++;
        else
          zeros++;
      if (ones != b && zeros != a)
        valid = false;
      ones = 0, zeros = 0;
      for (int i = 0; i < n; i++)
        if (y[i] == '1')
          ones++;
        else
          zeros++;
      if (ones != b && zeros != a)
        valid = false;
    }

    DEBUG printf("\tx = %s\n\ty = %s\n", x.c_str(), y.c_str());

    if (valid)
      printf("Yes\n%s\n%s\n", x.c_str(), y.c_str());
    else
      printf("No\n");
  }
  return 0;
}
