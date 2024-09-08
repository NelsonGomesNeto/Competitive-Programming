#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli A, B, a[maxN], b[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld %d", &A, &B, &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);
    
    vector<int> order;
    for (int i = 0; i < n; i++)
      order.push_back(i);

    bool possible = false;
    do
    {
      bool can = true;
      for (int i: order)
      {
        lli canDo = B / a[i] + (B % a[i] != 0);
        lli hits = b[i] / A + (b[i] % A != 0);
        if (canDo < hits)
          can = false;
        B -= hits * a[i];
      }
      possible |= can;
    } while (!possible && next_permutation(order.begin(), order.end()));
    

    printf("%s\n", possible ? "YES" : "NO");
  }
  return 0;
}