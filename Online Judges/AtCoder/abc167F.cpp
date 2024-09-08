#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
char ss[maxN + 1];
string s[maxN];
struct Node
{
  int diff, index;
  bool operator<(const Node &other) const
  {
    return diff > other.diff;
  }
};

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    vector<Node> mids;
    string left = "", right = "";
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      s[i] = string(ss);

      int open = 0, close = 0;
      for (int j = 0; j < s[i].size(); j++)
        open += s[i][j] == '(', close += s[i][j] == ')';

      if (close == 0) left += s[i];
      else if (open == 0) right += s[i];
      else mids.push_back(Node{open - close, i});
    }
    sort(mids.begin(), mids.end());
    string mid = "";
    for (int i = 0; i < mids.size(); i++)
      mid += s[mids[i].index];
    string ans = left + mid + right;

    bool can = true;
    int open = 0;
    for (int i = 0; i < ans.size(); i++)
    {
      open += ans[i] == '(' ? 1 : -1;
      if (open < 0) can = false;
    }
    if (open) can = false;
    DEBUG printf("\t%s - %s %s %s\n", ans.c_str(), left.c_str(), mid.c_str(), right.c_str());

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}