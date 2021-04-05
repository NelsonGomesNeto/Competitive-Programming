#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
char a[maxN + 1], b[maxN + 1];

vector<int> flippable;
bool flippablePos[maxN];
vector<pair<int, int>> wrongBlocks;

bool cmp(char s, char t, bool flipped)
{
  if (flipped)
    return s != t;
  return s == t;
}

int memo[maxN][2];
int solve(int i = n - 1, bool flipped = false)
{
  if (i == -1) return true;
  int &ans = memo[i][flipped];
  if (ans != -1)
    return ans;

  ans = 0;
  if (cmp(a[i], b[i], flipped))
    ans = solve(i - 1, flipped);
  else if (flippablePos[i])
    ans = solve(i - 1, !flipped);
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", a);
    scanf(" %s", b);

    for (int i = 0; i < n; i++)
      flippablePos[i] = false;
    flippable.clear();
    for (int i = 0, o = 0, z = 0; i < n; i++)
    {
      o += a[i] == '1', z += a[i] == '0';
      if (o == z)
        flippable.push_back(i), flippablePos[i] = true;
    }

    for (int i = 0; i < n; i++)
      memo[i][0] = memo[i][1] = -1;
    bool can = solve();

    DEBUG printf("\t%s\n\t%s\n", a, b);

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
