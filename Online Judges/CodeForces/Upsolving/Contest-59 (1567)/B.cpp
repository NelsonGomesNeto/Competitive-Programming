#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
int mexor[maxN + 1];

int main()
{
  mexor[0] = 0;
  for (int i = 1; i <= maxN; i++)
    mexor[i] = i ^ mexor[i - 1];

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int a, b; scanf("%d %d", &a, &b);
    DEBUG printf("\t%d %d\n", mexor[a - 1], mexor[a - 1] ^ b);
    int ans = a;
    if (mexor[a - 1] == b)
      ;
    else
    {
      ans++;
      if ((mexor[a - 1] ^ b) == a)
        ans++;
    }

    printf("%d\n", ans);
  }
  return 0;
}
