#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
char ss[maxN + 1];

int main()
{
  scanf(" %s", ss);
  string s = string(ss);
  reverse(s.begin(), s.end());
  for (int i = 0; i < s.size(); i++)
    if (s[i] == '6')
      s[i] = '9';
    else if (s[i] == '9')
      s[i] = '6';
  printf("%s\n", s.c_str());

  return 0;
}