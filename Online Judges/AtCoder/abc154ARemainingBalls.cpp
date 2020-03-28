#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 11;
string s, t, u;
int a, b;
char ss[maxN], tt[maxN], uu[maxN];

int main()
{
  while (scanf(" %s %s", ss, tt) != EOF)
  {
    scanf("%d %d", &a, &b);
    scanf(" %s", uu);
    s = string(ss), t = string(tt), u = string(uu);

    a -= u == s;
    b -= u == t;
    printf("%d %d\n", a, b);
  }
  return 0;
}