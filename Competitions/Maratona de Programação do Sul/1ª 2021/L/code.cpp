#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10; int n; double l, q;
char ss[101 + 1];
string names[maxN];

int main()
{
  while (~scanf("%d %lf %lf", &n, &l, &q))
  {
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      names[i] = string(ss);
    }

    int ans = 0;
    while (q < l)
      l -= q, ans = (ans + 1) % n;
    printf("%s %.1lf\n", names[ans].c_str(), l);
  }
  return 0;
}