#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Store the positions of each x (let's call it xPositions), the permutation

  At first, the position == permutation, but transit from p_1 to p_2 by
    swap(permutation[1], permutation[2])
    pos[permutation[1]] = 1, pos[permutation[2]] = 2
    (And from p_2 to p_3 similar:
      swap(permutation[1], permutation[3])
      pos[permutation[1]] = 1, pos[permutation[3]] = 3
      But you must have done the transition from p_1 to p_2 before
    )

  Nice, we can emulate and precalculate the permutation and pos in O(n)
  Now, we just need to calculate f. For that, notice that the only changes
  from p_i to p_i + 1 are:
    sum of the neighbors of p[1] and p[i + 1]
  So, since we've store the positions of each x:
  for i in [2, n]
    ans[i] = ans[i - 1]
    remove the position difference from p[1]'s the neighbors
    remove the position difference from p[1]'s the neighbors
    make transition to i
    add the position difference from p[1]'s the neighbors
    add the position difference from p[1]'s the neighbors

  Notice that we won't ever need to iterate more than twice through the
  list of neighbors of any x. So: O(n + m) NICE
*/

const int maxN = 2e5 +1; int n, m;
int x[maxN], pos[maxN], permutation[maxN];
list<int> xPositions[maxN];
lli ans[maxN];

void sub(int at, int i)
{
  for (int j: xPositions[permutation[at]])
  {
    if (j + 1 <= m)
      ans[i] -= abs(pos[x[j]] - pos[x[j + 1]]);
    if (j - 1 >= 1)
      ans[i] -= abs(pos[x[j]] - pos[x[j - 1]]);
  }
}

void add(int at, int i)
{
  for (int j: xPositions[permutation[at]])
  {
    if (j + 1 <= m)
      ans[i] += abs(pos[x[j]] - pos[x[j + 1]]);
    if (j - 1 >= 1)
      ans[i] += abs(pos[x[j]] - pos[x[j - 1]]);
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  int x[m + 1];
  for (int i = 1; i <= m; i ++) scanf("%d", &x[i]);

  for (int i = 1; i <= m; i ++) xPositions[x[i]].push_back(i);
  for (int i = 1; i <= n; i ++) permutation[i] = pos[i] = i;
  for (int j = 1; j < m; j ++) ans[1] += abs(pos[x[j]] - pos[x[j + 1]]);

  for (int i = 2; i <= n; i ++)
  {
    ans[i] = ans[i - 1];
    sub(1, i), sub(i, i);

    swap(permutation[1], permutation[i]);
    pos[permutation[1]] = 1, pos[permutation[i]] = i;

    add(1, i), add(i, i);
  }

  for (int i = 1; i <= n; i ++)
    printf("%lld%c", ans[i], i < n ? ' ' : '\n');
  return 0;
}