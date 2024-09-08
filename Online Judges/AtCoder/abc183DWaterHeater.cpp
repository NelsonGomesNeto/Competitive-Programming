#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli w;
lli s[maxN], t[maxN], p[maxN];
lli in[maxN], out[maxN];

int main()
{
  while (scanf("%d %lld", &n, &w) != EOF)
  {
    memset(in, 0, sizeof(in)), memset(out, 0, sizeof(out));
    for (int i = 0; i < n; i++)
    {
      scanf("%lld %lld %lld", &s[i], &t[i], &p[i]);
      t[i]--;
      in[s[i]] += p[i];
      out[t[i]] += p[i];
    }

    bool can = true;
    lli curr = 0;
    for (int i = 0; i < maxN; i++)
    {
      curr += in[i];
      if (curr > w)
        can = false;
      curr -= out[i];
    }
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}