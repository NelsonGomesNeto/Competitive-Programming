#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 1e5;
lli letterValue[256], accSum[maxN + 1];
char s[maxN + 1]; int n;
map<lli, vector<int>> before[256], after[256];

int binSearch(vector<int> &a, int target)
{
  int lo = 0, hi = a.size() - 1;
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    if (a[mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  if (a[lo] < target && lo + 1 < a.size() && a[lo + 1] >= target) lo ++;
  return(a[lo] < target ? 0 : a.size() - lo);
}

int main()
{
  for (int i = 'a'; i <= 'z'; i ++) scanf("%lld", &letterValue[i]);
  scanf(" %s", s); n = strlen(s);
  for (int i = 0; i < n; i ++) accSum[i + 1] = accSum[i] + letterValue[s[i]];
  for (int i = 0; i < n; i ++)
  {
    before[s[i]][accSum[i]].push_back(i);
    if (letterValue[s[i]] != 0) after[s[i]][accSum[i + 1]].push_back(i);
  }

  lli total = 0;
  for (int i = 'a'; i <= 'z'; i ++)
    for (auto &j: letterValue[i] != 0 ? after[i] : before[i])
      if (before[i].count(j.first))
      {
        auto &k = before[i][j.first];
        DEBUG printf("%c, %lld | %d %d\n", i, j.first, (int) j.second.size(), (int) k.size());
        DEBUG printf("\tj: ");
        DEBUG for (int kk = 0; kk < j.second.size(); kk ++) printf("%d%c", j.second[kk], kk < j.second.size() - 1 ? ' ' : '\n');
        DEBUG printf("\tk: ");
        DEBUG for (int kk = 0; kk < k.size(); kk ++) printf("%d%c", k[kk], kk < k.size() - 1 ? ' ' : '\n');

        for (int jj: j.second)
        {
          int above = binSearch(k, jj + 1);
          DEBUG printf("j: %d, above: %d\n", jj, above);
          total += above;
        }
      }
  printf("%lld\n", total);

  return(0);
}