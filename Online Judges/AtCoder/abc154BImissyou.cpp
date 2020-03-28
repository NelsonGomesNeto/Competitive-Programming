#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
string s;
char ss[maxN];

int main()
{
  while (scanf(" %s", ss) != EOF)
  {
    s = string(ss);
    string ans = "";
    for (int i = 0; i < s.size(); i ++)
      ans += 'x';
    printf("%s\n", ans.c_str());
  }
  return 0;
}