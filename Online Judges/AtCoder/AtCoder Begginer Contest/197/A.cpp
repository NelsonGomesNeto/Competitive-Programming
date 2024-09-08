#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char str[4];
  scanf(" %s", str);
  string s = string(str);
  s = s.substr(1) + s[0];
  printf("%s\n", s.c_str());
  return 0;
}