#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e5; int n;
vector<lli> ua;
map<lli, int> compressed;
int cnt[maxN], cntcnt[maxN + 2]; lli acc[maxN + 2];
lli a[maxN], decompressed[maxN];
vector<pair<int, lli>> numbersByCount;

struct Ans { int size, n, m; void print() { printf("%d\n%d %d\n", size, n, m); }};

void printMatrix(int nn, int mm)
{
  int mat[nn][mm];
  memset(mat, 0, sizeof(mat));
  for (int i = 0, j = 0, jj = 0, at = 0, line = 0, done = 0; jj < mm; jj ++)
  {
    for (line = 0; line < nn; line ++, i = (i + 1) % nn, j = (j + 1) % mm, done ++)
    {
      if (done == min(nn, numbersByCount[at].first)) done = 0, at ++;
      mat[i][j] = numbersByCount[at].second;
    }
    if (mat[i][j] != 0)
      j = (j + 1) % mm;
  }
  for (int i = 0; i < nn; i ++)
    for (int j = 0; j < mm; j ++)
      printf("%d%c", mat[i][j], j < mm - 1 ? ' ' : '\n');
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    compressed.clear(), numbersByCount.clear();
    memset(cnt, 0, sizeof(cnt)), memset(cntcnt, 0, sizeof(cntcnt));
    ua.clear();
    ua.resize(n);
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      ua[i] = a[i];
    }

    sort(ua.begin(), ua.end());
    ua.resize(distance(ua.begin(), unique(ua.begin(), ua.end())));
    for (int i = 0; i < ua.size(); i ++)
      compressed[ua[i]] = i, decompressed[i] = ua[i];
    for (int i = 0; i < n; i ++)
    {
      a[i] = compressed[a[i]];
      cnt[a[i]] ++;
    }
    for (int i = 0; i < ua.size(); i ++)
      numbersByCount.push_back({cnt[i], decompressed[i]});
    sort(numbersByCount.begin(), numbersByCount.end(), greater<pair<int, lli>>());

    for (int i = 0; i < maxN; i ++)
      if (cnt[i])
        cntcnt[cnt[i]] ++;
    for (int i = maxN; i >= 0; i --)
      acc[i] = acc[i + 1] + cntcnt[i];

    Ans ans = {0, 0, 0};
    for (lli nn = 1, now = 0; nn <= n; nn ++)
    {
      now += acc[nn]; // amount of numbers with frequency at least nn
      int mm = now / nn;
      if (nn * mm > ans.size && mm >= nn)
        ans.size = nn * mm, ans.n = nn, ans.m = mm;
    }
    ans.print();
    printMatrix(ans.n, ans.m);
  }
  return 0;
}
