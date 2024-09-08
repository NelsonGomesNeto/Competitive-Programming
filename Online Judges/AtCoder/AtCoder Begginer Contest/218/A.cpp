#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10;

int main()
{
  int n;
  char s[8];
  scanf("%d", &n);
  scanf(" %s", s);
  printf("%s\n", s[n - 1] == 'o' ? "Yes" : "No");
  return 0;
}