#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
char ss[maxN];
bool has[maxN+10];
string s;

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

struct Node
{
  int lo, hi, index;
  bool operator<(const Node &other) const
  {
    return lo < other.lo || (lo == other.lo && hi < other.hi);
  }
  bool operator==(const Node &other) const
  {
    return lo == other.lo && hi == other.hi;
  }
};
Node nodes[maxN];
int rnk[maxN][30];
vector<int> buildSuffixArray2(string str)
{
  int n = str.size();
  for (int i = 0; i < n; i ++)
    rnk[i][0] = str[i];
  int k;
  for (k = 0; (1 << k) < n; k ++)
  {
    for (int i = 0; i < n; i ++)
      nodes[i] = {rnk[i][k], i + (1 << k) < n ? rnk[i + (1 << k)][k] : -1, i};
    sort(nodes, nodes+n);
    // countSort(nodes, n);
    for (int i = 0; i < n; i ++)
      rnk[nodes[i].index][k + 1] = (i && nodes[i] == nodes[i - 1]) ? rnk[nodes[i - 1].index][k + 1] : i;
  }
  vector<int> ans(n);
  for (int i = 0; i < n; i++) ans[rnk[i][k]] = i;
  return ans;
}

int binSearch(vector<int> &sa, string &str, int at, int lo, int hi, char target, bool upperBound = false)
{
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (at+sa[mid] == str.size() || str[at+sa[mid]] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (at+sa[mid] < str.size() && str[at+sa[mid]] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  if (at+sa[lo] == str.size() || str[at+sa[lo]] != target)
    return -1;
  return lo;
}

int biggestPalindrome(vector<int> &sa, string &str, string &otherStr)
{
  for (int k = 0; k < str.size(); k++)
    has[k] = true;
  int bp = 0;
  for (int at = 0, lo = 0, hi = sa.size() - 1; at < str.size(); at++)
  {
    int prvLo = lo, prvHi = hi;
    // while (lo < hi && (at+sa[lo] == otherStr.size() || otherStr[at+sa[lo]] < str[at])) lo++;
    // if (lo == hi && (at+sa[lo] == otherStr.size() || otherStr[at+sa[lo]] != str[at])) break;
    // while (hi > lo && (at+sa[hi] == otherStr.size() || otherStr[at+sa[hi]] > str[at])) hi--;
    // if (lo == hi && (at+sa[hi] == otherStr.size() || otherStr[at+sa[hi]] != str[at])) break;
    lo = binSearch(sa, otherStr, at, lo, hi, str[at]);
    if (lo == -1) break;
    hi = binSearch(sa, otherStr, at, lo, hi, str[at], true);
    if (hi == -1) break;

    for (int k = prvLo; k < lo; k++) has[sa[k]] = false;
    for (int k = hi + 1; k <= prvHi; k++) has[sa[k]] = false;

    DEBUG printf("\t\t\tmid %d %d %d\n", at, (int)str.size() - (at + (at + 1) + 1), (int)str.size() - (at + (at + 1)));
    if ((((int)str.size() - (at + (at + 1)))) >= 0 && has[(((int)str.size() - (at + (at + 1))))])
    {
      DEBUG printf("\t\t\t\tmid yes 1\n");
      bp = 2*(at + 1) - 1;
    }
    if ((((int)str.size() - (at + (at + 1) + 1))) >= 0 && has[(((int)str.size() - (at + (at + 1) + 1)))])
    {
      DEBUG printf("\t\t\t\tmid yes 2\n");
      bp = 2*(at + 1);
    }
  }
  return bp;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf(" %s", ss);
    s = string(ss);

    string ans;
    int i, j;
    for (i = 0, j = s.size() - 1; i <= j && s[i] == s[j]; i++, j--);
    i --, j++;

    if (i == j)
    {
      printf("%s\n", s.c_str());
      continue;
    }

    string middle = s.substr(i + 1, j - i - 1);
    string revMiddle = middle;
    reverse(revMiddle.begin(), revMiddle.end());
    vector<int> middleSa = buildSuffixArray(middle), revMiddleSa = buildSuffixArray(revMiddle);

    int iBest = i + biggestPalindrome(revMiddleSa, middle, revMiddle);
    int jBest = j - biggestPalindrome(middleSa, revMiddle, middle);

    DEBUG {
      printf("\t%d %d %d %d (%s | %s)\n", i, j, iBest, jBest, middle.c_str(), revMiddle.c_str());
      for (int i = 0; i < middleSa.size(); i++)
        printf("\t\t%d %s\n", middleSa[i], middle.c_str()+middleSa[i]);
      printf("\t\t-----\n");
      for (int i = 0; i < revMiddleSa.size(); i++)
        printf("\t\t%d %s\n", revMiddleSa[i], revMiddle.c_str()+revMiddleSa[i]);
    }

    if ((iBest - i) >= (j - jBest))
      ans = s.substr(0, iBest + 1) + s.substr(j);
    else
      ans = s.substr(0, i + 1) + s.substr(jBest);
    printf("%s\n", ans.c_str());
  }
  return 0;
}