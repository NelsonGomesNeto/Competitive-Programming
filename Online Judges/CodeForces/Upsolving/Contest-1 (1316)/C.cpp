#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, m; lli p;
lli a[maxN], b[maxN];

int main()
{
  while (scanf("%d %d %lld", &n, &m, &p) != EOF)
  {
    for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
    for (int i = 0; i < m; i ++) scanf("%lld", &b[i]);

    vector<bool> done(n + m - 1, false);
    // shuffle(all.begin(), all.end(), default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
    int ans;
    for (int j = 0; j < n + m - 1;)
    {
      ans = j;
      done[ans] = true;
      lli s = 0;
      for (int i = 0; i <= ans; i ++)
        if (i < n && ans - i < m)
          s = (s + a[i] * b[ans - i] % p) % p;
      DEBUG printf("\ts: %lld\n", s);
      if (s != 0)
        break;
      j = (j + s) % (n + m - 1);
      while (done[j]) j = (j + 1) % (n + m - 1);
    }
    printf("%d\n", ans);
  }
  return 0;
}
