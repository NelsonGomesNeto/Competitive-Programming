#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, k;
char s[maxN + 1];
int lt[maxN + 1], rt[maxN + 1], rem[maxN + 1];

int binarySearch(int sum[], int i, int lo, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    if (sum[mid] - sum[i] <= k) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d %d\n%s", &n, &k, s) != EOF)
  {
    memset(lt, 0, sizeof(lt)), memset(rt, 0, sizeof(rt)), memset(rem, 0, sizeof(rem));
    for (int i = 0; i < n; i ++)
    {
      lt[i + 1] = lt[i];
      rt[i + 1] = rt[i];
      rem[i + 1] = rem[i];
      if (i + 1 < n && s[i] == 'L' && s[i + 1] == 'R')
        lt[i + 1] ++;
      if (i + 1 < n && s[i] == 'R' && s[i + 1] == 'L')
        rt[i + 1] ++;
      if (i + 1 < n && s[i] == s[i + 1])
        rem[i + 1] ++;
    }

    // for (int i = 0; i <= n; i ++)
    //   printf("%d%c", lt[i], i < n ? ' ' : '\n');
    // for (int i = 0; i <= n; i ++)
    //   printf("%d%c", rt[i], i < n ? ' ' : '\n');

    int ans = 0;
    for (int i = 0; i < n; i ++)
    {
      int j = binarySearch(s[i] == 'L' ? lt : rt, i, i);
      ans = max(ans, j - i + rem[i] + (rem[n] - rem[j]));
    }
    printf("%d\n", ans);
  }

  return(0);
}