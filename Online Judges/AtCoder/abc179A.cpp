#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[1001];
  scanf("%s", s);
  string ss = string(s);
  if (ss[ss.size() - 1] == 's')
    ss += "es";
  else
    ss += "s";
  printf("%s\n", ss.c_str());
  return 0;
}