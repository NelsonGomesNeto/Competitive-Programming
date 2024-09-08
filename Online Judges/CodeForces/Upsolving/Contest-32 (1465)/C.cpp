#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
struct Rook
{
  int i, j; bool done;
  void read() { scanf("%d %d", &i, &j); i--, j--; done = i == j; }
};
Rook rooks[maxN];
set<int> uc, ur, ub;
set<int> udone;
map<int, set<int>> rows, columns;

set<int> cc, rr;
void applyOneRow(int i)
{
  //ur.count(rooks[i].j)

  DEBUG printf("Row: %d\n", i);
  ur.insert(rooks[i].i);
  if (uc.count(rooks[i].i))
    ub.insert(rooks[i].i);
  rr.insert(rooks[i].i);

  ur.erase(rooks[i].j);
  if (ub.count(rooks[i].j))
    ub.erase(rooks[i].j);
}
void applyOneColumn(int i)
{
  //uc.count(rooks[i].i)
  DEBUG printf("Column: %d\n", i);

  uc.insert(rooks[i].j);
  if (ur.count(rooks[i].j))
    ub.insert(rooks[i].j);
  cc.insert(rooks[i].j);

  uc.erase(rooks[i].i);
  if (ub.count(rooks[i].i))
    ub.erase(rooks[i].i);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n, m; scanf("%d %d", &n, &m);
    ub.clear(), uc.clear(), ur.clear();
    for (int i = 0; i < n; i++) ub.insert(i), uc.insert(i), ur.insert(i);
    rows.clear(), columns.clear();

    udone.clear();
    for (int i = 0; i < m; i++)
    {
      rooks[i].read();
      if (!rooks[i].done)
      {
        udone.insert(i);
        rows[rooks[i].i].insert(i);
        columns[rooks[i].j].insert(i);
      }
      ur.erase(rooks[i].i), uc.erase(rooks[i].j);

      if (ub.count(rooks[i].i))
        ub.erase(rooks[i].i);

      if (ub.count(rooks[i].j))
        ub.erase(rooks[i].j);
    }

    DEBUG {
      char s[n][n + 1];
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
          s[i][j] = '.';
        s[i][n] = '\0';
      }
      for (int i = 0; i < m; i++)
        s[rooks[i].i][rooks[i].j] = 'R';
      for (int i = 0; i < n; i++)
        printf("\t%s\n", s[i]);
    }

    int ans = 0;
    while (true)
    {
      list<int> toRemove;
      cc.clear(), rr.clear();
      for (int i: udone)
      {
        if (ur.count(rooks[i].j) && uc.count(rooks[i].i))
        {
          if (ur.count(rooks[i].i))
            applyOneRow(i);
          else
            applyOneColumn(i);

          ans++, toRemove.push_back(i);
        }
        else if (ur.count(rooks[i].j))
        {
          ans++, toRemove.push_back(i);
          applyOneRow(i);
        }
        else if (uc.count(rooks[i].i))
        {
          ans++, toRemove.push_back(i);
          applyOneColumn(i);
        }
      }
      for (int i: toRemove)
        udone.erase(i);

      while (cc.size() || rr.size())
      {
        set<int> nc = cc, nr = rr;
        cc.clear(), rr.clear();
        for (int r: nr)
        {
          list<int> tr;
          for (int i: rows[r])
            if (udone.count(i))
              applyOneRow(i), udone.erase(i);
            else
              tr.push_back(i);
          for (int i: tr)
            rows[r].erase(i);
        }
        for (int c: nc)
        {
          list<int> tr;
          for (int i: columns[c])
            if (udone.count(i))
              applyOneColumn(i), udone.erase(i);
            else
              tr.push_back(i);
          for (int i: tr)
            columns[c].erase(i);

        }
      }

      bool allDone = true;
      for (int i: udone)
      {
        ans += 2, udone.erase(i);
        assert(!ub.empty());
        int j = *ub.begin();

        ur.insert(rooks[i].i);
        if (uc.count(rooks[i].i))
          ub.insert(rooks[i].i);

        uc.insert(rooks[i].j);
        if (ur.count(rooks[i].j))
          ub.insert(rooks[i].j);

        ur.erase(j), uc.erase(j), ub.erase(j);
        allDone = false;
        break;
      }
      if (allDone) break;
    }

    printf("%d\n", ans);
  }
  return 0;
}
