#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5; int n, k;

set<int> programmers;
int teams[maxN], programmerToPosition[maxN + 1], positionToProgrammer[maxN];
int leftSkip[maxN], rightSkip[maxN];

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0, s; i < n; i ++)
  {
    scanf("%d", &s); leftSkip[i] = rightSkip[i] = i;
    programmers.insert(s), programmerToPosition[s] = i, positionToProgrammer[i] = s;
  }

  int team = 1;
  while (programmers.size())
  {
    int s = *(--programmers.end());
    vector<int> before, after; int lend = -1, rend = n;
    for (int i = programmerToPosition[s] - 1, kk = k; kk; i --)
    {
      while (i >= 0 && teams[i]) i = leftSkip[i];
      if (i < 0) break;
      before.push_back(i), kk --, lend = i - 1;
    }
    for (int i = programmerToPosition[s], kk = k + 1; kk; i ++)
    {
      while (i < n && teams[i]) i = rightSkip[i];
      if (i >= n) break;
      after.push_back(i), kk --, rend = i + 1;
    }
    while (lend >= 0 && teams[lend]) lend = leftSkip[lend];
    while (rend < n && teams[rend]) rend = rightSkip[rend];

    for (int i: before)
      teams[i] = team, programmers.erase(positionToProgrammer[i]), leftSkip[i] = lend, rightSkip[i] = rend;
    for (int i: after)
      teams[i] = team, programmers.erase(positionToProgrammer[i]), leftSkip[i] = lend, rightSkip[i] = rend;
    team = team == 1 ? 2 : 1;
  }
  for (int i = 0; i < n; i ++) printf("%d", teams[i]); printf("\n");

  return(0);
}