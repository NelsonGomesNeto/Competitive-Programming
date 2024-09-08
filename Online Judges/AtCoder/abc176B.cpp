#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
char s[maxN + 1];

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    int sum = 0;
    for (int i = 0; s[i]; i++)
      sum = (sum + (s[i] - '0')) % 9;
    printf("%s\n", sum % 9 == 0 ? "Yes" : "No");
  }
  return 0;
}