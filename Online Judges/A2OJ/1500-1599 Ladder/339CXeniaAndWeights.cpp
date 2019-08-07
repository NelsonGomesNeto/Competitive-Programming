#include <bits/stdc++.h>
using namespace std;

const int maxM = 1e3;
vector<int> weights; int m;
vector<int> toPut;

short memo[maxM][19][11];
bool solve(int i = 0, int left = 0, int right = 0, bool leftTurn = true, int prv = 0)
{
  if (i == m) return(true);
  if (abs(left - right) >= weights[0]) return(false);
  if (memo[i][9 - (left - right)][prv] == -1)
  {
    bool ans = false;
    for (int w: weights)
      if (w != prv
        && (leftTurn ? (left + w > right) : (right + w > left))
        && solve(i + 1, left + w*leftTurn, right + w*!leftTurn, !leftTurn, w))
      {
        ans = true;
        toPut.push_back(w);
        break;
      }
    memo[i][9 - (left - right)][prv] = ans;
  }
  return(memo[i][9 - (left - right)][prv]);
}

int main()
{
  for (int i = 0, a; i < 10; i ++)
  {
    scanf("%1d", &a);
    if (a) weights.push_back(i + 1);
  }
  scanf("%d", &m);
  if (m == 1 && weights.size() > 0) printf("YES\n%d\n", weights[0]);
  else if (weights.size() <= 1) printf("NO\n");
  else
  {
    reverse(weights.begin(), weights.end()), memset(memo, -1, sizeof(memo));
    if (!solve()) printf("NO\n");
    else
    {
      printf("YES\n"); reverse(toPut.begin(), toPut.end());
      for (int i = 0; i < toPut.size(); i ++) printf("%d%c", toPut[i], i < toPut.size() - 1 ? ' ' : '\n');
    }
  }
  return(0);
}