#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int p[maxN];

int memoRight[2][maxN];
int countRight(int i, bool xKind)
{
  if (i == n - 1)
    return 0;
  int &ans = memoRight[xKind][i];
  if (ans != -1) return ans;

  ans = 0;
  if (p[i + 1] < p[i])
    ans = 1 + countRight(i + 1, xKind);
  return ans;
}

int memoLeft[2][maxN];
int countLeft(int i, bool xKind)
{
  if (i == 0)
    return 0;
  int &ans = memoLeft[xKind][i];
  if (ans != -1) return ans;

  ans = 0;
  if (p[i - 1] < p[i])
    ans = 1 + countLeft(i - 1, xKind);
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i]);
      p[i]--;
    }

    map<int, int> cnt;
    memset(memoRight, -1, sizeof(memoRight));
    memset(memoLeft, -1, sizeof(memoLeft));
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
      int l = countLeft(i, true), r = countRight(i, true);
      if (!cnt.count(l)) cnt[l] = 0;
      cnt[l]++;
      if (!cnt.count(r)) cnt[r] = 0;
      cnt[r]++;

      if (l == r)
        mx = max(mx, l);
    }
    DEBUG printf("\t%d %d\n", cnt.rbegin()->first, cnt.rbegin()->second);

    if (cnt.rbegin()->second == 2 && mx == cnt.rbegin()->first)
      printf("%d\n", ~cnt.rbegin()->first & 1);
    else
      printf("0\n");

  }
  return 0;
}
