#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
char s[maxN][101];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf(" %[^\n]", s[i]);

    bool has = false;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (!strcmp(s[i], s[j]))
          has = true;
    printf("%s\n", has ? "Yes" : "No");
  }
  return 0;
}