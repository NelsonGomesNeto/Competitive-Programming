#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxK = 4, maxAlpha = 256; int n, m, k;
char ss[maxK + 1]; 
struct Block
{
  string s; int mt;
  void read()
  {
    scanf(" %s %d", ss, &mt);
    s = string(ss);
    mt--;
  }
  bool operator<(const Block &other) const { return s < other.s; }
};
Block blocks[maxN];
int binarySearch(int i, int a, bool upperBound, int lo = 0, int hi = m - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (blocks[mid].s[i] <= a) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (blocks[mid].s[i] >= a) hi = mid;
      else lo = mid + 1;
    }
  }
  return blocks[lo].s[i] == a ? lo : -1;
}

string p[maxN];
vector<int> graph[maxN];
int indegree[maxN];
// v depends on u
void addEdge(int u, int v)
{
  graph[u].push_back(v);
  indegree[v]++;
}

void addDependencies(int pp, int lo, int hi)
{
  DEBUG printf("\t\t%d - %s - %d %d\n", pp + 1, p[pp].c_str(), lo, hi);
  for (int i = lo; i <= hi; i++)
    if (pp != blocks[i].mt)
      addEdge(blocks[i].mt, pp);
}
void buildDependencies(int pp, int i = 0, int lo = 0, int hi = m - 1)
{
  DEBUG printf("\t\t%d - %s - %d - %d %d\n", pp, p[pp].c_str(), i, lo, hi);
  if (lo == -1)
    return;
  if (i == k)
  {
    addDependencies(pp, lo, hi);
    return;
  }

  char a = p[pp][i];
  if (a == '_')
  {
    for (a = 'a'; a <= 'z'; a++)
      buildDependencies(pp, i + 1, binarySearch(i, a, false, lo, hi), binarySearch(i, a, true, lo, hi));
  }
  else
    buildDependencies(pp, i + 1, binarySearch(i, a, false, lo, hi), binarySearch(i, a, true, lo, hi));
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    for (int i = 0; i < n; i++)
      graph[i].clear(), indegree[i] = 0;

    DEBUG {
      printf("-------------\n");
    }

    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      p[i] = string(ss);
    }
    bool can = true;
    for (int i = 0; i < m; i++)
    {
      blocks[i].read();
      bool valid = true;
      for (int j = 0; j < k; j++)
        if (p[blocks[i].mt][j] != '_' && p[blocks[i].mt][j] != blocks[i].s[j])
          valid = false;
      can &= valid;
    }

    sort(blocks, blocks+m);

    for (int i = 0; i < n; i++)
      buildDependencies(i);

    DEBUG {
      for (int i = 0; i < n; i++)
      {
        printf("\t%d - %s (%d) -", i + 1, p[i].c_str(), indegree[i]);
        for (int v: graph[i])
          printf(" %d", v + 1);
        printf("\n");
      }
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
      if (indegree[i] == 0)
        q.push(i);
    vector<int> ans;
    while (!q.empty())
    {
      int u = q.front(); q.pop();
      DEBUG printf("\t%d\n", u + 1);
      ans.push_back(u);
      for (int v: graph[u])
        if (--indegree[v] == 0)
          q.push(v);
    }

    if (!can || ans.size() != n) printf("NO\n");
    else
    {
      printf("YES\n");
      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i] + 1, i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
