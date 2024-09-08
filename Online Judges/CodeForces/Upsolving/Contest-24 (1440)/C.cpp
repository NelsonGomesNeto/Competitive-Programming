#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, m;
char s[maxN][maxN + 1];

struct Pos
{
  int i, j;
  void print(char end) { printf("%d %d%c", i + 1, j + 1, end); }
  Pos shift(int ii, int jj)
  {
    return Pos{i + ii, j + jj};
  }
  void apply()
  {
    s[i][j] = s[i][j] == '1' ? '0' : '1';
  }
};
struct Op
{
  vector<Pos> p;
  void print() { for (int i = 0; i < 3; i++) p[i].print(i < 2 ? ' ' : '\n'); }
  Op shift(int ii, int jj)
  {
    Op other;
    for (int i = 0; i < 3; i++)
      other.p.push_back(p[i].shift(ii, jj));
    return other;
  }
  void apply()
  {
    for (int i = 0; i < 3; i++)
      p[i].apply();
  }
};
vector<Op> ans;

int ones(int i, int j)
{
  int cnt = 0;
  for (int ii = 0; ii < 2; ii++)
    for (int jj = 0; jj < 2; jj++)
      cnt += s[i + ii][j + jj] == '1';
  return cnt;
}

map<string, vector<Op>> opMap[5];
void remAllThrees();
void addOp(int i, int j, int cnt)
{
  DEBUG printf("\taddOp: %d %d, cnt: %d\n", i, j, cnt);
  if (cnt == 3)
  {
    Op op;
    for (int ii = 0; ii < 2; ii++)
      for (int jj = 0; jj < 2; jj++)
        if (s[i + ii][j + jj] == '1')
          op.p.push_back(Pos{i + ii, j + jj});
    if (op.p.size() != 3) return;
    op.apply();
    ans.push_back(op);
  }
  else // 1 2 4
  {
    string t = "";
    for (int ii = 0; ii < 2; ii++)
      for (int jj = 0; jj < 2; jj++)
        t += s[i + ii][j + jj];
    DEBUG printf("\t\tt: %s\n", t.c_str());
    for (Op &op: opMap[cnt][t])
    {
      Op hehe = op.shift(i, j);
      hehe.apply();
      ans.push_back(hehe);
    }
  }

  remAllThrees();

  DEBUG
    for (int j = 0; j < n; j++)
      printf("\t\t%s\n", s[j]);
}

void remAllThrees()
{
  for (int i = 0; i + 1 < n; i++)
    for (int j = 0; j + 1 < m; j++)
      if (ones(i, j) == 3)
        addOp(i, j, 3);
}

int main()
{
  Pos p0 = {0, 0}, p1 = {0, 1}, p2 = {1, 0}, p3 = {1, 1};
  opMap[4]["1111"].push_back(Op{{p0, p1, p2}});

  opMap[1]["1000"].push_back(Op{{p0, p1, p2}});
  opMap[1]["0100"].push_back(Op{{p0, p1, p3}});
  opMap[1]["0010"].push_back(Op{{p0, p2, p3}});
  opMap[1]["0001"].push_back(Op{{p2, p3, p1}});

  opMap[2]["1001"].push_back(Op{{p0, p1, p2}});
  opMap[2]["0110"].push_back(Op{{p0, p1, p3}});
  opMap[2]["1100"].push_back(Op{{p2, p3, p0}});
  opMap[2]["0011"].push_back(Op{{p0, p1, p2}});

  opMap[2]["1010"].push_back(Op{{p1, p3, p0}});
  opMap[2]["0101"].push_back(Op{{p0, p2, p1}});

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
      s[i][m] = '\0';
      scanf(" %s", s[i]);
    }

    vector<int> bestOrder = {3, 4, 3, 2, 3, 1, 3};
    ans.clear();
    for (int cnt: bestOrder)
    {
      DEBUG printf("here %d\n", cnt);
      for (int i = 0; i + 1 < n; i++)
        for (int j = 0; j + 1 < m; j++)
          if (ones(i, j) == cnt)
          {
            addOp(i, j, cnt);
            if (cnt == 1)
            {
              addOp(i, j, 2);
              addOp(i, j, 3);
            }
            if (cnt == 2)
              addOp(i, j, 3);
            if (cnt == 4)
            {
              addOp(i, j, 1);
              addOp(i, j, 2);
              addOp(i, j, 3);
            }
          }
      DEBUG
        for (int i = 0; i < n; i++)
          printf("\t%s\n", s[i]);
    }

    printf("%d\n", (int)ans.size());
    for (Op &op: ans)
      op.print();
  }
  return 0;
}