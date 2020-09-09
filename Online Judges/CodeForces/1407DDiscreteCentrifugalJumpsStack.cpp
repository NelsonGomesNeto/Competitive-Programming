#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  For each skyscraper i: it might go to 3 others
    1: above jump to j (max(h[i], h[j]) < min(h[i + 1 : j - 1]))
      if h[i] >= h[j]
        you need to find the first skyscraper <= h[i]
      if h[i] < h[j]:
        same as above, but from j to i
    2: below jump to j (min(h[i], h[j]) > max(h[i + 1 : j - 1]))
      very similar to above
    3: jump to i + 1
      very basic, nothing to do here

  After calculation the next for each i: use DP to find the choice of jumps
*/

const int maxN = 3e5; int n;
const lli inf = 1e9 + 1;
lli h[maxN];

list<int> nxtOver[maxN], nxtBelow[maxN];
int memo[maxN];
int solve(int i = 0)
{
  if (i >= n - 1) return 0;
  if (memo[i] != -1) return memo[i];

  int ans = 1e6;
  for (int j: nxtOver[i])
    ans = min(ans, solve(j) + 1);
  for (int j: nxtBelow[i])
    ans = min(ans, solve(j) + 1);
  ans = min(ans, solve(i + 1) + 1);
  return memo[i] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &h[i]);
      nxtOver[i].clear(), nxtBelow[i].clear();
    }

    stack<pair<int, int>> st;
    for (int i = 0; i < n; i++) // 1 - h[i] >= h[j]
    {
      while (!st.empty() && h[i] > st.top().first)
        st.pop();
      if (!st.empty())
        nxtOver[st.top().second].push_back(i);
      st.push({h[i], i});
    }

    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) // 1 - h[i] < h[j]
    {
      while (!st.empty() && h[i] > st.top().first)
        st.pop();
      if (!st.empty())
        nxtOver[i].push_back(st.top().second);
      st.push({h[i], i});
    }

    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) // 2 - h[i] <= h[j]
    {
      while (!st.empty() && h[i] < st.top().first)
        st.pop();
      if (!st.empty())
        nxtBelow[st.top().second].push_back(i);
      st.push({h[i], i});
    }

    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) // 2 - h[i] > h[j]
    {
      while (!st.empty() && h[i] < st.top().first)
        st.pop();
      if (!st.empty())
        nxtBelow[i].push_back(st.top().second);
      st.push({h[i], i});
    }

    DEBUG {
      for (int i = 0; i < n; i++)
        printf("%3d%c", i, i < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i++)
        printf("%3lld%c", h[i], i < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i++)
        if (!nxtOver[i].empty())
        {
          printf("%d -", i);
          for (int j: nxtOver[i])
            printf(" %d", j);
          printf("\n");
        }
      for (int i = 0; i < n; i++)
        if (!nxtBelow[i].empty())
        {
          printf("%d -", i);
          for (int j: nxtBelow[i])
            printf(" %d", j);
          printf("\n");
        }
    }

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}