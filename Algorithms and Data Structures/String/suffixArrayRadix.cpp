#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
char s[maxN + 1];

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

int main()
{
  while (~scanf(" %s", s))
  {
    vector<int> sa = buildSuffixArray(string(s));

    for (int i = 0; i < sa.size(); i ++)
      printf("%d %s\n", sa[i], s+sa[i]);
    printf("---------------\n");
  }

  return 0;
}