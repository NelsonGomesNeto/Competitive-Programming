#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e4 + 1; int n;
char s[maxN];
int l[10][maxN];

struct PIN
{
  int a, b, c;
  bool operator<(const PIN &other) const
  {
    return a < other.a || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c);
  }
};

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", s);
    for (int i = 0; i < 10; i ++)
      l[i][n] = n;
    for (int i = n - 1; i >= 0; i --)
    {
      for (int j = 0; j < 10; j ++)
        l[j][i] = l[j][i + 1];
      l[s[i] - '0'][i] = i;
    }

    set<PIN> ans;
    for (int i = 0; i < n - 2; i ++)
      for (int j = 0; j < 10; j ++)
      {
        int pos = l[j][i + 1];
        if (pos == n) continue;
        for (int k = 0; k < 10; k ++)
          if (l[k][pos + 1] != n)
            ans.insert(PIN{s[i] - '0', j, k});
      }
    printf("%d\n", (int) ans.size());
  }
  return 0;
}