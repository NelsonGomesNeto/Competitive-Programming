#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int n = 8;
char ss[n + 1];
string mat[n];

int main()
{
  for (int i = 0; i < n; ++i)
  {
    scanf(" %s", ss);
    mat[i] = string(ss);
  }

  string ans = "";
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (mat[i][j] == '*')
      {
        DEBUG printf("%d %d\n", i, j);
        ans = (char)('a' + j) + to_string(n - i);
      }
  printf("%s\n", ans.c_str());
  return 0;
}
