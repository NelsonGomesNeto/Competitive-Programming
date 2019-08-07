#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  You *will* have to choose k - 1 points to cut
  The full array sum is: a[n - 1] - a[0]
  Each point i you choose will remove exactly a[i + 1] - a[i] from the answer
  So just choose the k - 1 biggest points of cut
*/

const int maxN = 3e5; int n, k;
lli a[maxN], diff[maxN - 1];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n - 1; i ++)
      diff[i] = a[i + 1] - a[i];
    sort(diff, diff+n-1); reverse(diff, diff+n-1);

    lli ans = a[n - 1] - a[0];
    for (int i = 0; i < k - 1; i ++)
      ans -= diff[i];
    printf("%lld\n", ans);
  }
  return(0);
}