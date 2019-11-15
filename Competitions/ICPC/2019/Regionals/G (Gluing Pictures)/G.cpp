#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1; int n;
char s[maxN], t[maxN];
int ranking[maxN];

const int alphabet = 256;
vector<int> sortCycleShifts(string &str)
{
  int sz = str.size();
  vector<int> p(sz), c(sz), cnt(max(sz, alphabet), 0);

  for (int i = 0; i < sz; i ++)
    cnt[str[i]] ++;
  for (int i = 1; i < alphabet; i ++)
    cnt[i] += cnt[i - 1];
  for (int i = 0; i < sz; i ++)
    p[-- cnt[str[i]]] = i;
  c[p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < sz; i ++)
  {
    classes += str[p[i]] != str[p[i - 1]];
    c[p[i]] = classes - 1;
  }

  vector<int> newP(sz), newC(sz);
  for (int k = 0; (1 << k) < sz; k ++)
  {
    for (int i = 0; i < sz; i ++)
    {
      newP[i] = p[i] - (1 << k);
      if (newP[i] < 0) newP[i] += sz;
    }
    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (int i = 0; i < sz; i ++)
      cnt[c[newP[i]]] ++;
    for (int i = 1; i < classes; i ++)
      cnt[i] += cnt[i - 1];
    for (int i = sz - 1; i >= 0; i --)
      p[-- cnt[c[newP[i]]]] = newP[i];
    newC[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < sz; i ++)
    {
      classes += c[p[i]] != c[p[i - 1]] || c[(p[i] + (1 << k)) % sz] != c[(p[i - 1] + (1 << k)) % sz];
      newC[p[i]] = classes - 1;
    }
    c.swap(newC);
  }

  return p;
}
vector<int> buildSuffixArray(string str)
{
  str += "$";
  vector<int> sortedShifts = sortCycleShifts(str);
  sortedShifts.erase(sortedShifts.begin());
  return sortedShifts;
}

int letterCnt[26], startPos[26], endPos[26];
int nextPos(char str[], int j)
{
  int low = startPos[str[j] - 'A'], high = endPos[str[j] - 'A'], at = 1;
  DEBUG printf("\t%s %d - %d %d\n", str, j, low, high);
  while (low < high && str[j + at])
  {
    int lo = low, hi = high;
    // lowerBound
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      if (ranking[mid] + at < n && str[j + at] <= s[ranking[mid] + at])
        hi = mid;
      else
        lo = mid + 1;
    }
    low = lo;
    lo = low, hi = high;
    // upperBound
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if (ranking[mid] + at >= n || str[j + at] >= s[ranking[mid] + at])
        lo = mid;
      else
        hi = mid - 1;
    }
    high = lo;
    DEBUG printf("\t\t%d %d %d\n", low, high, at);
    if (ranking[lo] + at >= n || s[ranking[lo] + at] != str[j + at])
      break;
    lo = low, hi = high, at ++;
  }
  while (ranking[low] + at < n && s[ranking[low] + at] == str[j + at])
    at ++;
  DEBUG printf("\tchoose: %d | %d\n", low, at);
  return j + at;
}

int main()
{
  while (scanf("%s", s) != EOF)
  {
    n = strlen(s);
    memset(letterCnt, 0, sizeof(letterCnt));
    for (int i = 0; i < n; i ++) letterCnt[s[i] - 'A'] ++;

    vector<int> sa = buildSuffixArray(string(s));
    for (int i = 0; i < sa.size(); i ++) ranking[i] = sa[i];

    for (int i = 0; i < n; i ++)
    {
      int j = i;
      while (j + 1 < n && s[ranking[j + 1]] == s[ranking[i]]) j ++;
      startPos[s[ranking[i]] - 'A'] = i, endPos[s[ranking[i]] - 'A'] = j;
      i = j;
    }
    DEBUG {
      for (int i = 0; i < n; i ++)
        printf("%3d - %3d %s\n", i, ranking[i], s+ranking[i]);
    }

    int q; scanf("%d", &q);
    while (q --)
    {
      scanf(" %s", t);
      DEBUG printf("query: %s\n", t);
      int j = 0, ans = 0;
      for (int i = 0; t[i]; i ++)
        if (!letterCnt[t[i] - 'A'])
          ans = -1;
      if (ans == -1)
        printf("-1\n");
      else
      {
        while (t[j])
          j = nextPos(t, j), ans ++;
        printf("%d\n", ans);
      }
    }
    getchar();
  }
  return 0;
}