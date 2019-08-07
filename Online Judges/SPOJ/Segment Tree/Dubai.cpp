#include <bits/stdc++.h>
using namespace std;
const int maxSize = 1e6, maxLog = floor(log2(1e6)) + 1;
int sparseTable[maxSize][maxLog + 1], logDP[maxSize + 1];
int zero = 0;

int f(int a, int b)
{
  return(max(a, b));
}

void build(int array[], int n, int logn)
{
  for (int i = 0; i < n; i ++) sparseTable[i][0] = array[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i + shift < n; i ++)
      sparseTable[i][j] = f(sparseTable[i][j - 1], sparseTable[i + shift][j - 1]);
}

int query(int lo, int hi)
{
  int qs = logDP[hi - lo + 1];
  return(f(sparseTable[lo][qs], sparseTable[hi - (1 << qs) + 1][qs]));
  int ans = zero;
  for (int j = maxLog; j >= 0; j --)
    if (lo + (1 << j) - 1 <= hi)
    {
      ans = f(ans, sparseTable[lo][j]);
      lo += (1 << j);
    }
  return(ans);
}

void fillLogDP()
{
  logDP[1] = 0;
  for (int i = 2; i <= maxSize; i ++) logDP[i] = logDP[i >> 1] + 1;
}

int main()
{
  int n; scanf("%d", &n);
  map<int, vector<int>> tie;
  int heights[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &heights[i]);
    tie[heights[i]].push_back(i);
  }
  build(heights, n, floor(log2(n)) + 1); fillLogDP();

  int f; scanf("%d", &f);
  while (f --)
  {
    int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
    int ans = query(lo, hi);
    printf("%d", ans);
    for (vector<int>::iterator i = lower_bound(tie[ans].begin(), tie[ans].end(), lo); i != tie[ans].end() && *i <= hi; i ++)
      printf(" %d", (*i) + 1);
    printf("\n");
  }
  return(0);
}
