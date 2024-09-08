#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n, k; scanf("%d %d", &n, &k);
    string ans = "", base = "abc";
    for (int i = 0; i < n; i++)
      ans += base[i % 3];
    printf("%s\n", ans.c_str());
  }
  return 0;
}
// abcabc
// acb