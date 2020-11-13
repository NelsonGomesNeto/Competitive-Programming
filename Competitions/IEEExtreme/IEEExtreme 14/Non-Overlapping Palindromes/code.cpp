#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char ss[maxN + 1];
string s;

vector<int> d1;
vector<int> d2;
void manacher(string &str)
{
  d1.resize(str.size());
  d2.resize(str.size());
  int l = 0, r = -1;
  for (int i = 0; i < str.size(); i++)
  {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < str.size() && s[i - k] == s[i + k])
      k++;
    d1[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k, r = i + k;
  }
  l = 0, r = -1;
  for (int i = 0; i < str.size(); i++)
  {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < str.size() && s[i - k - 1] == s[i + k])
      k++;
    d2[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k - 1, r = i + k;
  }
}

int extractPal(int bestK, int position, int type)
{
  if (type == 1)
  {
    if (bestK == 1) return 1;
    int lo = position - bestK + 1;
    int hi = lo + bestK + 1;

    string pal = s.substr(lo, hi - lo + 1);
    string aux = "";
    for (int i = 0; i < s.size(); i++)
    {
      if (i >= lo && i <= hi) continue;
      aux += s[i];
    }
    s = aux;
    DEBUG printf("t1 %s - %s - %d %d %d\n", pal.c_str(), aux.c_str(), bestK, position, type);
    return pal.size();
  }
  else
  {
    int lo = position - bestK;
    int hi = lo + bestK * 2 - 1;

    string pal = s.substr(lo, bestK * 2);
    string aux = "";
    for (int i = 0; i < s.size(); i++)
    {
      if (i >= lo && i <= hi) continue;
      aux += s[i];
    }
    s = aux;
    DEBUG printf("t2 %s - %s - %d %d %d\n", pal.c_str(), aux.c_str(), bestK, position, type);
    return pal.size();
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    s = string(ss);
    string hehe = s;
    reverse(hehe.begin(), hehe.end());
    n = s.size();

    int ans = 0;

    if (s == hehe)
      printf("%d\n", (int)hehe.size() - 1);
    else
    {
      for (int k = 0; k < 2; k++)
      {
        manacher(s);
        int bestK = 0, position = 1, type = 1;
        for (int i = 0; i < n; i++)
        {
          if (d1[i] > bestK)
            bestK = d1[i], position = i, type = 1;
          if (d2[i] >= bestK)
            bestK = d2[i], position = i, type = 2;
        }
        DEBUG printf("here %s || %d %d %d\n", s.c_str(), bestK, position, type);
        ans += extractPal(bestK, position, type);
        n = s.size();
      }
      printf("%d\n", ans);
    }


  }
  return 0;
}