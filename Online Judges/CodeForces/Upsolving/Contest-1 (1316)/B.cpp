#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3 + 1; int n;
char ss[maxN];
string s, ans;

string rev(int k)
{
  string aux = "";
  for (int i = k - 1; i < n; i ++)
    aux += s[i];
  if ((n - k) & 1)
    for (int i = 0; i <= k - 2; i ++)
      aux += s[i];
  else
    for (int i = k - 2; i >= 0; i --)
      aux += s[i];
  return aux;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    scanf(" %s", ss);
    s = string(ss);

    int k = 1;
    ans = s;
    for (int kk = 2; kk <= n; kk ++)
    {
      string aux = rev(kk);
      DEBUG printf("\t%d - %s\n", kk, aux.c_str());
      if (aux < ans)
        k = kk, ans = aux;
    }
    printf("%s\n%d\n", ans.c_str(), k);
  }
  return 0;
}
/*
abc def
c bad ef
cd abe f
cde baf
cde fab
*/
