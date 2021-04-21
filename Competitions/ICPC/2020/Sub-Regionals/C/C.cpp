#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxS = 1e6; int m, n;
char str[maxS + 1];
vector<string> a, b;
bool aUsed[maxN], bUsed[maxN];

map<string, vector<pair<int, int>>> as, bs;
bool isPrefix(string &s, string &t)
{
  return s.size() < t.size() && s == t.substr(0, s.size());
}
void fill(map<string, vector<pair<int, int>>> &s, vector<string> &ins, bool isB = false)
{
  sort(ins.begin(), ins.end());
  for (int i = 0; i + 1 < ins.size(); i++)
  {
    int j = i + 1;
    while (j < ins.size() && isPrefix(ins[i], ins[j]))
    {
      string hehe = ins[j].substr(ins[i].size());
      if (isB) reverse(hehe.begin(), hehe.end());
      s[hehe].push_back({i, j});
      j++;
    }
  }
  DEBUG {
    for (auto &it: s)
    {
      printf("\t%s:\n", it.first.c_str());
      for (auto &p: it.second)
        printf("\t\t(%d, %d) - (%s, %s)\n", p.first, p.second, ins[p.first].c_str(), ins[p.second].c_str());
    }
    printf("-----------\n");
  }
}

int main()
{
  scanf("%d %d", &m, &n);
  a.resize(m);
  for (int i = 0; i < m; i++)
  {
    scanf(" %s", str);
    a[i] = string(str);
  }
  b.resize(n);
  for (int i = 0; i < n; i++)
  {
    scanf(" %s", str);
    b[i] = string(str);
    reverse(b[i].begin(), b[i].end());
  }

  fill(as, a);
  fill(bs, b, true);

  for (auto &it: as)
    if (bs.count(it.first))
    {
      for (auto &p: it.second)
        aUsed[p.first] = aUsed[p.second] = true;
      for (auto &p: bs[it.first])
        bUsed[p.first] = bUsed[p.second] = true;
    }

  int aAns = 0, bAns = 0;
  for (int i = 0; i < m; i++)
    aAns += !aUsed[i];
  for (int i = 0; i < n; i++)
    bAns += !bUsed[i];
  printf("%d %d\n", aAns, bAns);

  return 0;
}