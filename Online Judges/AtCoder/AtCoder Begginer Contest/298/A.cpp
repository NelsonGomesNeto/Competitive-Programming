#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
char s[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", s);
    bool oneGood = false;
    bool noPoor = true;
    for (int i = 0; i < n; ++i)
    {
      if (s[i] == 'o')
        oneGood = true;
      if (s[i] == 'x')
        noPoor = false;
    }
    bool passed = oneGood && noPoor;
    printf("%s\n", passed ? "Yes" : "No");
  }
  return 0;
}
