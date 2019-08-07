#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli x[4]; for (int i = 0; i < 4; i ++) scanf("%lld", &x[i]);
  lli a, b, c;
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
      if (i != j) 
        for (int k = 0; k < 4; k ++)
          if (k != i && k != j)
            for (int n = 0; n < 4; n ++)
              if (n != i && n != j && n != k)
              {
                a = x[i] - x[j], b = x[i] - x[k], c = x[i] - x[n];
                if (a + b == x[n] && a + c == x[k] && b + c == x[j] && a + b + c == x[i])
                {
                  printf("%lld %lld %lld\n", a, b, c);
                  return(0);
                }
              }
  return(0);
}