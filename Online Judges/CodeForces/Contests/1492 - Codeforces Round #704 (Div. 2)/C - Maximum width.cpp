#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
char ss[maxN + 1];
string s, t;
vector<int> pos[256];
int ldone[maxN], rdone[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    scanf(" %s", ss); s = string(ss);
    scanf(" %s", ss); t = string(ss);
    for (int i = 'a'; i <= 'z'; i++)
      pos[i].clear();
    for (int i = 0; i < n; i++)
      pos[s[i]].push_back(i);

    int finishingPos;
    for (int i = n - 1, j = m - 1; j >= 0; j--, i--)
    {
      while (s[i] != t[j])
        i--;

      rdone[j] = i;
    }
    for (int i = 0, j = 0; j < m; j++, i++)
    {
      while (s[i] != t[j])
        i++;
      ldone[j] = i;
    }

    DEBUG {
      for (int i = 0; i < m; i++)
        printf("%d%c", ldone[i], i < m - 1 ? ' ' : '\n');
      for (int i = 0; i < m; i++)
        printf("%d%c", rdone[i], i < m - 1 ? ' ' : '\n');
    }

    // set<pair<char, char>> pairs;
    // for (int i = 1; i < m; i++)
    //   pairs.insert(make_pair(t[i - 1], t[i]));

    // int ans = 1;
    // for (auto &[l, r]: pairs)
    // {
    //   for (int i = 0; i < m; i++)
    //     if (t[i] == l)

    //   printf("\t%c %c | %d %d\n", l, r, i, j);

    //   if (i < n && j >= 0 && s[i] == l && s[j] == r)
    //     ans = max(ans, j - i);
    // }
    int ans = 1;
    for (int i = 1; i < m; i++)
      if (rdone[i] > ldone[i - 1])
        ans = max(ans, rdone[i] - ldone[i - 1]);
    printf("%d\n", ans);
  }
  return 0;
}
