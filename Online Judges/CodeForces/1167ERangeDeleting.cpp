#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  We will count this way:
    for each i in [0, x - 1]:
      ans += x - last
      it's ascending for: f(i, last), where last is [p, x]
        p is the (smallest value where f(0, p) is ascenfing) or
        (the biggest value before the last occurrence of i).
      But only while firstOccurrence[i] > lastOccurrence of the previous
      number present.
  First, we find the smallest value where f(0, p) is ascending.
  For that, we must store the first and last occurrence of every number.
  So, we start p from x - 1, and will keep going down until the last
  occurrence of p is bigger than the first occurrence of the next number
  present.

  Now we can count using the counting method described above.
*/

const int maxN = 1e6, maxX = 1e6; int n, x;
int a[maxN];
int firstOccurrence[maxX], lastOccurrence[maxN];
int before[maxN];

int main()
{
  scanf("%d %d", &n, &x);
  memset(firstOccurrence, -1, sizeof(firstOccurrence));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]); a[i] --;
    if (firstOccurrence[a[i]] == -1) firstOccurrence[a[i]] = i;
    lastOccurrence[a[i]] = i;
    before[i] = i == 0 ? a[i] : max(before[i - 1], a[i]);
  }
  int p = 0, firstPosition = n;
  for (p = x - 1; p >= 0; p --)
  {
    if (firstOccurrence[p] == -1) continue;
    if (lastOccurrence[p] > firstPosition) break;
    firstPosition = firstOccurrence[p];
  }
  // printf("%d\n", p);

  lli ans = 0; int lastPosition = -1;
  for (int i = 0; i < x; i ++)
  {
    int m = max(i, p);
    if (lastPosition != -1) m = max(m, before[lastPosition]);
    ans += x - m;
    // printf("%d %d %lld\n", i, m, ans);
    if (firstOccurrence[i] != -1)
    {
      if (firstOccurrence[i] < lastPosition) break;
      lastPosition = lastOccurrence[i];
    }
  }
  printf("%lld\n", ans);

  return(0);
}
