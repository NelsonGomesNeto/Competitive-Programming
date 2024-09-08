#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 30;
char s[maxN + 1];

int match(vector<string> &a, vector<string> &b)
{
  int an = a.size(), am = a[0].size(), bn = b.size(), bm = b[0].size();
  int best = 0;
  for (int si = -(bn - 1); si < bn; si++)
    for (int sj = -(bm - 1); sj < bm; sj++)
    {
      int matches = 0;
      for (int ai = si, bi = 0; ai < an && bi < bn; ai++, bi++)
        for (int aj = sj, bj = 0; aj < am && bj < bm; aj++, bj++)
          if (ai >= 0 && ai < an && aj >= 0 && aj < am && bi >= 0 && bi < bn && bj >= 0 && bj < bm)
            matches += a[ai][aj] == '#' && b[bi][bj] == '#';
      best = max(best, matches);
    }
  return best;
}

void flipH(vector<string> &a)
{
  for (int i = 0; i < a.size(); i++)
    for (int j = 0, end = a[0].size() >> 1; j < end; j++)
      swap(a[i][j], a[i][a[0].size() - j - 1]);
}
void flipV(vector<string> &a)
{
  for (int i = 0; i < a.size(); i++)
    for (int j = 0, end = a[0].size() >> 1; j < end; j++)
      swap(a[a.size() - i - 1][j], a[i][j]);
}
void rotate90(vector<string> &a)
{
  vector<string> other(a[0].size());
  for (int j = 0; j < a[0].size(); j++)
    other[j].resize(a.size());

  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < a[0].size(); j++)
      other[j][a.size() - i - 1] = a[i][j];

  a = other;
}

void print(vector<string> &a)
{
  printf("-----\n");
  for (int i = 0; i < a.size(); i++)
    printf("%s\n", a[i].c_str());
  printf("-----\n");
}

int an, am, bn, bm;
vector<string> a, b;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &an, &am);
    a.clear();
    a.resize(an);
    for (int i = 0; i < an; i++)
    {
      scanf(" %s", s);
      a[i] = string(s);
    }

    scanf("%d %d", &bn, &bm);
    b.clear();
    b.resize(bn);
    for (int i = 0; i < bn; i++)
    {
      scanf(" %s", s);
      b[i] = string(s);
    }

    DEBUG {
      print(a);
      print(b);
    }
    auto originalA = a, originalB = b;

    int ans = 0;
    for (int hehe = 0; hehe < 2; hehe++)
    {
      for (int k = 0; k < 4; k++)
      {
        ans = max(ans, match(a, b));
        rotate90(b);
        for (int kk = 0; kk < 2; kk++)
        {
          for (int kkk = 0; kkk < 2; kkk++)
          {
            ans = max(ans, match(a, b));
            flipH(a);
            ans = max(ans, match(a, b));
            flipV(a);
          }
          flipH(b);
          for (int kkk = 0; kkk < 2; kkk++)
          {
            ans = max(ans, match(a, b));
            flipH(a);
            ans = max(ans, match(a, b));
            flipV(a);
          }
          flipV(b);
        }
      }
      a = originalB, b = originalA;
    }

    printf("%d\n", ans);
  }
  return 0;
}