#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
lli mod = (lli) 1e9 + 7;
char n[101], sequence[100001];
int nSize, sequenceSize, s[100001];
lli dp[100001];

void printTra(int q)
{
  printf("--> ");
  for (int k = 0; k < q; k ++)
  {
    for (int l = !k ? 0 : s[k - 1] + 1; l <= s[k]; l ++)
      printf("%c", sequence[l]);
    printf("%c", k < q - 1 ? ' ' : '\n');
  }
}

int smaller(int start, int size)
{
  int bigger = -1;
  for (int i = 0; bigger == -1 && i < size; i ++)
    if (sequence[start + i] > n[i]) bigger = 1;
    else if (sequence[start + i] < n[i]) bigger = 0;
  if (bigger == -1) bigger = sequence[start] > n[0];
  return(!bigger);
}

lli findAll(int i, int q)
{
  DEBUG printf("%d\n", i);
  if (i == sequenceSize)
  {
    DEBUG printTra(q);
    return(1);
  }
  if (sequence[i] == '0') return(0);
  int at = i;
  if (dp[at] == -1)
  {
    int ans = 0, size = 1;
    while (i < sequenceSize && size < nSize)
    {
      s[q] = i;
      ans = (ans + findAll(i + 1, q + 1)) % mod;
      i ++; size ++;
    }
    DEBUG printf("%d %d\n", i, size);
    if (smaller(at, size))
    {
      s[q] = i;
      ans = (ans + findAll(i + 1, q + 1)) % mod;
    }
    dp[at] = ans;
  }
  return(dp[at]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  scanf("%s\n%s", n, sequence);
  nSize = strlen(n); sequenceSize = strlen(sequence);

  lli ans = findAll(0, 0);
  printf("%lld\n", ans);
  return(0);
}