#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
lli a[maxN];
set<lli> done;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    done.clear();
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    bool can = true;
    for (int i = 0; i < n; i++)
    {
      lli p = ((i + a[i]) % n + n) % n;
      if (done.count(p)) can = false;
      else done.insert(p);
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
