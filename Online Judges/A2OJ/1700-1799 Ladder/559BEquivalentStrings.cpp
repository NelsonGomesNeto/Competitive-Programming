#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char a[maxN + 1], b[maxN + 1];
int ac[26][maxN + 1], bc[26][maxN + 1];

bool fastCompare(int ai, int bi, int sz)
{
  if (sz > 100)
    for (int i = 0; i < 26; i ++)
      if (ac[i][ai + sz] - ac[i][ai] != bc[i][bi + sz] - bc[i][bi])
        return false;
  for (int i = 0; i < sz; i ++)
    if (a[ai + i] != b[bi + i])
      return false;
  return true;
}

bool equi(int ai = 0, int bi = 0, int sz = n)
{
  if (n == 0) return false;
  if (fastCompare(ai, bi, sz)) return true;
  if (sz & 1) return false;

  int mid = sz >> 1;
  return (equi(ai, bi, mid) && equi(ai + mid, bi + mid, mid)) || (equi(ai, bi + mid, mid) && equi(ai + mid, bi, mid));
}

string smallest(string s)
{
  if (s.size() & 1) return s;
  int half = s.size() >> 1;
  string aa = smallest(s.substr(0, half));
  string bb = smallest(s.substr(half, half));
  if (aa < bb) return aa + bb;
  return bb + aa;
}

int main()
{
  int t = 0;
  while (scanf("%s %s", a, b) != EOF)
  {
    if (t ++) memset(ac, 0, sizeof(ac)), memset(bc, 0, sizeof(bc));

    getchar(), n = strlen(a);
    // for (int i = 0; i < n; i ++)
    //   for (int j = 0; j < 26; j ++)
    //   {
    //     ac[j][i + 1] = ac[j][i] + (a[i] - 'a' == j);
    //     bc[j][i + 1] = bc[j][i] + (b[i] - 'a' == j);
    //   }
    // printf("%s\n", equi() ? "YES" : "NO");
    printf("%s\n", smallest(a) == smallest(b) ? "YES" : "NO");
  }

  return 0;
}