#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50, maxP = 5e5; int n, p;
char s[maxN][maxP + 1], x[maxP + 1];

bool check(int i, int l, int r)
{
  for (int j = l; j <= r; j++)
    if (s[i][j] != x[j])
      return false;
  return true;
}
int has(int l, int r)
{
  for (int i = 0; i < n; i++)
    if (check(i, l, r))
      return i;
  return -1;
}

int main()
{
  while (~scanf("%d %d", &p, &n))
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);
    scanf(" %s", x);
    string xx = string(x);

    for (int i = 0; i < p; i++)
    {
      int j = i;
      list<int> has;
      for (int k = 0; k < n; k++)
        if (s[k][i] == x[i])
          has.push_back(k);

      while (j + 1 < p && !has.empty())
      {
        list<int> nxt;
        for (int k: has)
          if (s[k][j + 1] == x[j + 1])
            nxt.push_back(k);
        if (!nxt.empty()) j++, has = nxt;
        else break;
      }

      // printf("\t%d %d | %s\n", i, j, xx.c_str());
      int ans = has.empty() ? -1 : *has.begin();
      if (ans >= 0) ans++;
      printf("%s %d\n", xx.substr(i, j - i + 1).c_str(), ans);
      i = j;
    }
  }
  return 0;
}