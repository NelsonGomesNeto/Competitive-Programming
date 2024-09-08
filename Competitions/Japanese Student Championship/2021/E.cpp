#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int k;
char ss[maxN + 1];
string s;
int posCnt[maxN];
set<pair<int, int>> obligatory;
int letterCntPerPos[maxN][26];

bool valid = true;
int dfsCount(int lo = 0, int hi = s.size() - 1, int kk = 0)
{
  if (lo > hi || kk == k)
  {
    if (kk != k)
      valid = false;
    if (lo == hi)
      valid = false;
    if (lo < hi)
      obligatory.insert({lo, hi});
    return lo > hi ? 0 : 1;
  }
  DEBUG printf("\t%d %d %d\n", lo, hi, kk);

  for (int i = lo, j = hi; i <= hi; i++)
    posCnt[i]++, letterCntPerPos[i][s[i] - 'a']++;

  int sz = hi - lo + 1, toAdd = 0;
  if (sz & 1)
  {
    int mid = (lo + hi) >> 1;
    toAdd += dfsCount(lo, mid - 1, kk + 1);
    toAdd += dfsCount(mid + 1, hi, kk + 1);
  }
  else
  {
    int mid = (lo + hi) >> 1;
    toAdd += dfsCount(lo, mid, kk + 1);
    toAdd += dfsCount(mid + 1, hi, kk + 1);
  }
  return toAdd;
}

int main()
{
  int tt = 0;
  while (~scanf("%d", &k))
  {
    if (tt++)
    {
      memset(posCnt, 0, sizeof(posCnt));
      memset(letterCntPerPos, 0, sizeof(letterCntPerPos));
    }
    scanf(" %s", ss);
    s = string(ss);

    valid = true;
    obligatory.clear();
    int toAdd = dfsCount();

    if (!valid)
      printf("impossible\n");
    else
    {
      int toValid = 0;
      for (int i = 0, j = s.size() - 1; i <= j; i++, j--)
      {
        int total = posCnt[i] + posCnt[j];
        int best = total;
        for (int letter = 0; letter < 26; letter++)
          best = min(best, total - letterCntPerPos[i][letter] - letterCntPerPos[j][letter]);
        toValid += best;
      }
      printf("%d\n", max(toValid, toAdd));
    }
  }
  return 0;
}