#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  I will index by 1

  Rules:
    1 - a[i] = b[i] + c[i]
    2 - b[i] <= b[i + 1]
    3 - c[i] >= c[i + 1]
    4 - minimize max(b[i], c[i])
      simplification:
        minimize max(b[n], c[1])

  Notice the following:
  if a[i] <= a[i + 1]:
    increasing, we can only account for this increase using b,
    since c can't increase; with that said:
    b[i + 1] = b[i] + (a[i + 1] - a[i]), rule 5
  if a[i] > a[i + 1]:
    the opposite of above's reasoning:
    c[i + 1] = c[i] + (a[i + 1] - a[i]), rule 6

  We have a simple rule to define the best possible fit to b and c.
  But we don't know which value to insert on b[1] or c[1].

  Suppose c[1] = x:
    b[1] = a[1] - c[1] = a[1] - x, by rule 1
    b[2] = b[1] + max(0, a[1 + 1] - a[1]), by rule 5 and 6
    b[3] = b[2] + max(0, a[2 + 1] - a[2]), by rule 5 and 6
      b[3] = b[1] + max(0, a[1 + 1] - a[1]) + max(0, a[2 + 1] - a[2])
    ...
    b[n] = b[1] + sum(max(0, a[i + 1] - a[i]), i = [1 : n - 1])
      let's call that sum as deltaB

    Now c[1] = x, b[n] = a[1] - x + deltaB
    Since we want to minimize max(c[1], b[n]), and both are inversely dependent
      (decreasing c[1] will increase b[n], and vice versa;
      this happens because of x in c[1] and -x in b[n])
      Let's make them as equal as possible, so none will be standing out on the max:
      c[1] = b[n]
      x = a[1] - x + deltaB
      2 * x = a[1] + deltaB
      x = (a[1] + deltaB) / 2
      Hey, we found x! ^~^
        (x isn't necessarily the answer, but we can find it with it)

  Nice, but how do we update stuff? (addition of v in a[l : r])
  Notice that only a[1] and a[i + 1] - a[i] can effectively change x
  update a[1] whenever l == 1, add v
  update a[l] - a[l - 1], add v
  update a[r + 1] - a[r], add -v
  recalculate x
  It strongly recomend to store in another array the values of a[i + 1] = a[i]
  and update directly there. Forget about "a" (except for a[1]).

  (But you can use "a", it's just that you will probably a segtree or something
  to properly update them)

*/

const int maxN = 1e5; int n, q;
lli a[maxN];

lli delta[maxN - 1];
lli deltaSum = 0;
lli getAns()
{
  lli c1 = (a[0] + deltaSum) >> 1LL;
  lli bn = a[0] - c1 + deltaSum;
  return max(c1, bn);
}

int main()
{
  int tt = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (tt++) printf("\n");

    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    deltaSum = 0;
    for (int i = 0; i < n - 1; i++)
    {
      delta[i] = a[i + 1] - a[i];
      deltaSum += max(0LL, delta[i]);
    }

    printf("%lld\n", getAns());

    scanf("%d", &q);
    while (q--)
    {
      int l, r; lli x; scanf("%d %d %lld", &l, &r, &x); l--, r--;
      if (l)
      {
        deltaSum -= max(0LL, delta[l - 1]);
        delta[l - 1] += x;
        deltaSum += max(0LL, delta[l - 1]);
      }
      if (r + 1 < n)
      {
        deltaSum -= max(0LL, delta[r]);
        delta[r] -= x;
        deltaSum += max(0LL, delta[r]);
      }
      a[l] += x;

      printf("%lld\n", getAns());
    }
  }
  return 0;
}