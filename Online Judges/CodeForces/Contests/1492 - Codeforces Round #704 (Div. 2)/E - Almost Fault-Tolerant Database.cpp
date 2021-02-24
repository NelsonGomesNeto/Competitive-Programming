#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, m;
vector<vector<lli>> s;
vector<lli> ans;

bool solve(int i = 1, int changes = 0)
{
  if (i == n)
  {
    ans = s[0];
    return true;
  }

  vector<int> diffPos;
  for (int j = 0; j < m; j++)
    if (s[0][j] != s[i][j] && diffPos.size() < 6)
      diffPos.push_back(j);
  if (diffPos.size() <= 2)
    return solve(i + 1, changes);

  int reqChanges = diffPos.size() - 2;
  if (changes + reqChanges <= 2)
  {
    do
    {
      int aux[reqChanges];
      for (int j = 0; j < reqChanges; j++)
      {
        aux[j] = s[0][diffPos[j]];
        s[0][diffPos[j]] = s[i][diffPos[j]];
      }

      if (solve(1, changes + reqChanges))
        return true;

      for (int j = 0; j < reqChanges; j++)
        s[0][diffPos[j]] = aux[j];
    } while (next_permutation(diffPos.begin(), diffPos.end()));
  }

  return false;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    s.clear();
    s.resize(n, vector<lli>(m));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        scanf("%lld", &s[i][j]);

    bool can = solve();
    if (can)
    {
      printf("Yes\n");
      for (int i = 0; i < m; i++)
        printf("%lld%c", s[0][i], i < m - 1 ? ' ' : '\n');
    }
    else
      printf("No\n");
  }
  return 0;
}
