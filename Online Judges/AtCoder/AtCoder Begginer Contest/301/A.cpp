#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", ss);
    s = string(ss);

    int a = 0, t = 0;
    int winner = 0; char ans;
    for (int i = 0; i < n; ++i)
    {
      a += s[i] == 'A';
      t += s[i] == 'T';
      if (a > winner) winner = a, ans = 'A';
      if (t > winner) winner = t, ans = 'T';
    }

    printf("%c\n", ans);
  }
  return 0;
}
