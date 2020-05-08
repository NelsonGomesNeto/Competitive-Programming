#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3 + 1;
const lli limit = 1e9;
char ss[maxN];
string s;
int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, 1, -1};
int opMap[256]; char ops[5] = "NSEW";

lli fix(lli i)
{
  return ((i % limit) + limit) % limit;
}

struct Pos
{
  lli i, j;
  void move(char op, bool fixing = true)
  {
    i = fixing ? fix(i + di[opMap[op]]) : i + di[opMap[op]];
    j = fixing ? fix(j + dj[opMap[op]]) : j + dj[opMap[op]];
  }
  void operator+=(const Pos &other)
  {
    i = fix(i + other.i);
    j = fix(j + other.j);
  }
  Pos operator*(const lli k)
  {
    return Pos{fix(i * k), fix(j * k)};
  }
};

Pos solve(int i = 0, int end = s.size())
{
  Pos delta = Pos{0, 0};
  if (i >= end) return delta;
  DEBUG printf("\t%d %d - %c\n", i, end, s[i]);

  if (s[i] >= 'A' && s[i] <= 'Z')
  {
    delta.move(s[i]);
    delta += solve(i + 1, end);
  }
  else if (s[i] >= '0' && s[i] <= '9')
  {
    int start = i + 2;
    lli times = s[i++] - '0';
    i++;
    int op = 1;
    while (op)
    {
      if (s[i] == ')') op--;
      else if (s[i] == '(') op++;
      i++;
    }
    i--;

    delta += solve(start, i) * times;
    delta += solve(i + 1, end);
  }

  return delta;
}

int main()
{
  for (int i = 0; i < 4; i++) opMap[ops[i]] = i;

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    s = string(ss);

    Pos now = solve();

    printf("Case #%d: %lld %lld\n", tt, now.j + 1, now.i + 1);
  }
  return 0;
}