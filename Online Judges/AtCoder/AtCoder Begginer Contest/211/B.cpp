#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char ss[5];
  set<string> a;
  for (int i = 0; i < 4; i++)
  {
    scanf(" %s", ss);
    a.insert(string(ss));
  }
  printf("%s\n", a.size() == 4 ? "Yes" : "No");
  return 0;
}