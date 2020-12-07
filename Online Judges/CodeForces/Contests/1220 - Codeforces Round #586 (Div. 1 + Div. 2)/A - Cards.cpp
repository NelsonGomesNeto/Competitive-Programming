#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
int cnt[256];

int main()
{
  scanf("%d\n", &n);
  for (int i = 0; i < n; i ++)
  {
    char a; scanf("%c", &a);
    cnt[a] ++;
  }

  int ones = min({cnt['o'], cnt['n'], cnt['e']});
  cnt['o'] -= ones, cnt['n'] -= ones, cnt['e'] -= ones;
  int zeros = min({cnt['z'], cnt['e'], cnt['r'], cnt['o']});

  vector<int> ans;
  for (int i = 0; i < ones; i ++) ans.push_back(1);
  for (int i = 0; i < zeros; i ++) ans.push_back(0);
  for (int i = 0; i < ans.size(); i ++)
    printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');

  return(0);
}
