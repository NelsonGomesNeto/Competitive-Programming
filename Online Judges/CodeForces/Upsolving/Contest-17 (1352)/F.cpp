#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
a -> 00
b -> 01 or 10
c -> 11
*/

const int maxN = 101;
int a, b, c;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d %d", &a, &b, &c);
    int aa = a, bb = b, cc = c;
    int aaa = a, bbb = b, ccc = c;
    string ans = "";

    if (a) ans = "0";
    while (a) ans += "0", a--;
    if (b) { b -= !ans.empty(); ans += "1"; }
    while (b > 1) ans += "01", b -= 2;
    if (c && (ans.empty() || ans.back() != '1')) ans += "1";
    while (c) ans += "1", c--;
    if (b) ans += ans.empty() ? "01" : (ans.back() == '1' ? "0" : "1"), b--;

    for (int i = 1; i < ans.size(); i++)
      if (ans[i - 1] == ans[i])
        aa -= ans[i] == '0', cc -= ans[i] == '1';
      else
        bb--;
    printf("%s\n", ans.c_str());
    if (!(aa == 0 && bb == 0 && cc == 0))
      printf("\t%d %d %d || %d %d %d\n", aa, bb, cc, aaa, bbb, ccc);
  }
  return 0;
}
