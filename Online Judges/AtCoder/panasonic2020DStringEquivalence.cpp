#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 11;
int n;

vector<int> normalize(vector<int> s)
{
  int numMap[26];
  memset(numMap, -1, sizeof(numMap));
  for (int i = 0, c = 0; i < s.size(); i ++)
  {
    if (numMap[s[i]] == -1)
      numMap[s[i]] = c ++;
    s[i] = numMap[s[i]];
  }
  return s;
}

set<vector<int>> ans, nxt;
void solve()
{
  ans.clear(), nxt.clear();
  ans.insert({0});
  for (int i = 1; i < n; i ++)
  {
    nxt.clear();
    for (vector<int> s: ans)
    {
      s.push_back(0);
      for (int i = 0; i < 26; i ++)
      {
        s[s.size() - 1] = i;
        nxt.insert(normalize(s));
      }
    }
    ans = nxt;
  }
}

int main()
{
  int t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t ++) printf("--------------------\n");
    solve();
    for (vector<int> s: ans)
    {
      for (int i = 0; i < n; i ++)
        printf("%c", 'a' + s[i]);
      printf("\n");
    }
  }
  return 0;
}