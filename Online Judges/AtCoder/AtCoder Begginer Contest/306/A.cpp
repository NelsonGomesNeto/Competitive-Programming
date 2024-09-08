#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50;
int n;
char ss[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", ss);
    string s = string(ss);
    string ans;
    for (char c : s)
    {
      ans += c;
      ans += c;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}
