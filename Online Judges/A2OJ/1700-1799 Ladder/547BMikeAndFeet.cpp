#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Let's first solve another problem:
    max(j), where a[j] < a[i] and j < i
      For every i, let's save it as: l[i] = max(j)

    That can be done using stack or dp
    stack:
      for every i:
        while (stack isn't empty and a[stack.top()] >= a[i])
          stack.pop()
        l[i] = -1 if stack is empty else stack.top()
        stack.push(i)
    dp:
      for every i:
        j = i - 1
        while (j >= 0 && a[j] >= a[i]) j = l[j]
        l[i] = j
    (You will also need to solve:
    min(j), where a[j] < a[i] and j > i; but it's the same idea
    And save it in r[i])

  Nice, but why we have to solve that?
  With that, we will be able to know the left and right limits in which
  all numbers inside those limits are bigger than or equal to a[i]
  So, a[i] is the minimum inside that limit and we can be sure that
  the asnwer with size at least (right - left - 1) is >= a[i]

  To build the answer, just save the maximum a[i] in it's limits size
  And fill the remaining gaps with: ans[i] = max(ans[i], ans[i + 1])
*/

const int maxN = 2e5 + 1; int n;
int memo[maxN], a[maxN], l[maxN], r[maxN];

void stackPrecalculation()
{
  stack<int> s;
  for (int i = 0; i < n; i ++)
  {
    while (!s.empty() && a[s.top()] >= a[i]) s.pop();
    l[i] = s.empty() ? -1 : s.top();
    s.push(i);
  }
  while (!s.empty()) s.pop();
  for (int i = n - 1; i >= 0; i --)
  {
    while (!s.empty() && a[s.top()] >= a[i]) s.pop();
    r[i] = s.empty() ? n : s.top();
    s.push(i);
  }
}

void dpPrecalculation()
{
  l[0] = -1;
  for (int i = 1, j; i < n; i ++)
  {
    for (j = i - 1; j >= 0 && a[j] >= a[i]; j = l[j]);
    l[i] = j;
  }
  r[n - 1] = n;
  for (int i = n - 2, j; i >= 0; i --)
  {
    for (j = i + 1; j < n && a[j] >= a[i]; j = r[j]);
    r[i] = j;
  }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      memo[0] = i ? max(memo[0], a[i]) : a[i];
      memo[n - 1] = i ? min(memo[n - 1], a[i]) : a[i];
    }

    // stackPrecalculation();
    dpPrecalculation();

    for (int i = 0; i < n; i ++) memo[r[i] - l[i] - 2] = max(memo[r[i] - l[i] - 2], a[i]);
    for (int i = n - 2; i >= 0; i --) memo[i] = max(memo[i], memo[i + 1]);

    DEBUG {
      for (int i = 0; i < n; i ++) printf("%d%c", l[i] + 1, i < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i ++) printf("%d%c", r[i] + 1, i < n - 1 ? ' ' : '\n');
    }

    for (int i = 0; i < n; i ++)
      printf("%d%c", memo[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}