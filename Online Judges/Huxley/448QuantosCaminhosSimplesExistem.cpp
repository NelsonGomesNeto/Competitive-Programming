#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 4e3; int n, origin, destination;
map<string, int> stringToInt;
string intToString[maxN];
vector<int> graph[maxN];

void read(int i)
{
  char s[100], end; scanf("%s", s);
  string ss = s;
  if (!stringToInt.count(ss)) stringToInt[ss] = stringToInt.size();
  int u = stringToInt[ss];
  while (scanf("%c", &end) != EOF && end == ' ')
  {
    scanf("%s", s); ss = s;
    if (!stringToInt.count(ss)) stringToInt[ss] = stringToInt.size();
    graph[u].push_back(stringToInt[ss]);
  }
}

void printSpaces(int spaces) { while (spaces --) printf("   "); }
int memo[maxN];
int dfs(int u = origin, int depth = 0)
{
  if (u == destination) return 1;
  // printSpaces(depth);
  // printf("%d\n", u);
  if (memo[u] == -1)
  {
    memo[u] = 0;
    for (int v: graph[u])
      memo[u] += dfs(v, depth + 1);
  }
  return memo[u];
}

int main()
{
  scanf("%d\n", &n);
  for (int i = 0; i < n; i ++)
    read(i);

  char uu[100], vv[100];
  scanf("%s %s", uu, vv);
  string uuu = uu, vvv = vv;
  origin = stringToInt[uuu], destination = stringToInt[vvv];
  memset(memo, -1, sizeof(memo));
  int ans = dfs();
  printf("%d\n", ans);

  return(0);
}