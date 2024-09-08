#include <bits/stdc++.h>
#define DEBUG if(0)
#define DEBUG2 if(0)
#define DEBUG3 if (0 && tt > 6 && tt != 6) continue;
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, k;
char s[maxN + 1];
int e[maxN];
int subtreeSize[maxN], level[maxN];
int myGroupIndexes[maxN], myGroupSizes[maxN];
struct Edge
{
  int to, idx, uidx;
};
vector<Edge> tree[maxN];

void printTree(int u = 0, int prv = -1, int depth = 0)
{
  for (int i = 0; i < depth; i++) printf("   ");
  printf("%c%d\n", s[u], u + 1);

  for (Edge &e: tree[u])
    if (e.to != prv)
      printTree(e.to, u, depth + 1);
}

vector<vector<int>> groups;
struct GroupInfo
{
  int groupSize, infectedEdges, groupIdx, myIdx;
  bool operator<(const GroupInfo &other) const
  {
    return groupSize > other.groupSize;
  }
};
vector<GroupInfo> groupInfos;
void dfs(int u = 0, int prv = -1, int curr = 0)
{
  subtreeSize[u] = 1;
  if (s[u] == '*')
  {
    if (groups.size() <= curr) groups.push_back(vector<int>());
    groups[curr].push_back(u);
  }

  for (Edge &e: tree[u])
    if (e.to != prv)
    {
      level[e.to] = level[u] + 1;
      if (s[e.to] == '*' && s[u] == '#')
      {
        groups.push_back(vector<int>());
        dfs(e.to, u, groups.size() - 1);
      }
      else
        dfs(e.to, u, curr);
      subtreeSize[u] += subtreeSize[e.to];
    }
}

// Use Tree DP to optimize this further
/*
  #-*, *-#, #-# are potencial infected edges
  Here in the forth case, we need to sum the infectedEdges for each pair of
  group.
  Which is the same as sum the amount of times each potencial edge
  will be separating a pair of groups.

  So, for each each, we need to know how many big groups are before and after it
    infectedEdgesSum += before * after
*/
int subtreeBigGroups[maxN];
void dfsBigGroups(int u = 0, int prv = -1, bool inGroup = false)
{
  if (s[u] == '#') inGroup = false;
  if (myGroupSizes[u] == groupInfos[0].groupSize && !inGroup)
    subtreeBigGroups[u]++, inGroup = true;

  for (Edge &e: tree[u])
    if (e.to != prv)
    {
      dfsBigGroups(e.to, u, inGroup);
      subtreeBigGroups[u] += subtreeBigGroups[e.to];
    }
}
lli dfsSumInfectedEdges(int u = 0, int prv = -1)
{
  lli total = 0;
  for (Edge &e: tree[u])
    if (e.to != prv)
    {
      if (s[u] == '#' || s[e.to] == '#')
        total += (lli)subtreeBigGroups[e.to] * (subtreeBigGroups[0] - subtreeBigGroups[e.to]);
      total += dfsSumInfectedEdges(e.to, u);
    }
  return total;
}

void dfs3(int u, int prv, int targetSize, int infectedEdges = 1)
{
  if (s[u] == '*' && s[prv] == '#' && myGroupSizes[u] == targetSize)
    groupInfos[myGroupIndexes[u]].infectedEdges += infectedEdges;

  for (Edge &e: tree[u])
    if (e.to != prv)
      dfs3(e.to, u, targetSize, infectedEdges + (s[e.to] == '#' || s[u] == '#'));
}
void kind3FixInfectedEdges(GroupInfo &groupInfo, int targetSize)
{
  for (int u: groups[groupInfo.groupIdx])
    for (Edge &e: tree[u])
      if (s[e.to] == '#')
        dfs3(e.to, u, targetSize);
}

pair<bool, int> dist(int u, int target, int prv = -1, int d = 0)
{
  if (u == target) return make_pair(true, d);

  for (Edge &e: tree[u])
    if (e.to != prv)
    {
      pair<bool, int> hehe = dist(e.to, target, u, d + 1);
      if (hehe.first)
        return hehe;
    }
  return make_pair(false, 0);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %s", &n, &k, s);
    for (int i = 1; i <= k; i++)
    {
      int p; scanf("%d", &p);
      e[i] = p;
    }
    lli a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
    for (int i = k + 1; i < n; i++)
      e[i] = (((a * e[i - 2] + b * e[i - 1] + c) % (i)) + 1);

    for (int i = 0; i < n; i++)
      tree[i].clear(), myGroupIndexes[i] = myGroupSizes[i] = subtreeBigGroups[i] = 0;
    for (int i = 1; i < n; i++)
    {
      e[i]--;
      tree[i].push_back(Edge{e[i], 2*i - 1, i});
      tree[e[i]].push_back(Edge{i, 2*i, i});
    }

    DEBUG3

    DEBUG {
      printf("E: "); for (int i = 1; i < n; i++) printf("%d%c", e[i] + 1, i < n - 1 ? ' ' : '\n');
      printf("Tree:\n"); printTree();
    }

    groups.clear();
    dfs();
    DEBUG {
      printf("Groups %d:\n", (int)groups.size());
      for (int i = 0; i < groups.size(); i++)
      {
        printf("\t");
        for (int j = 0; j < groups[i].size(); j++)
          printf("%d%c", groups[i][j] + 1, j < groups[i].size() - 1 ? ' ' : '\n');
        if (groups[i].empty()) printf("\n");
      }
    }

    groupInfos.clear();
    for (int i = 0; i < groups.size(); i++)
      groupInfos.push_back(GroupInfo{(int)groups[i].size(), 0, i});
    sort(groupInfos.begin(), groupInfos.end());
    for (int i = 0; i < groupInfos.size(); i++)
    {
      groupInfos[i].myIdx = i;
      for (int u: groups[groupInfos[i].groupIdx])
        myGroupIndexes[u] = i, myGroupSizes[u] = groupInfos[i].groupSize;
    }

    DEBUG {
      printf("Group infos: ");
      for (int i = 0; i < groupInfos.size(); i++)
        printf("(%d, %d)%c", groupInfos[i].groupSize, groupInfos[i].infectedEdges, i < groupInfos.size() - 1 ? ' ' : '\n');
      if (groupInfos.empty()) printf("\n");
    }

    /*
      There are 4 cases:
      1: There is no group
      2: There is a single group
      3: The biggest group happens once
      4: The biggest group happens multiple times
    */
    lli maxReachable, ways;
    if (groupInfos.empty())
    {
      DEBUG2 { printf("\tkind 1\n"); fflush(stdout); }
      maxReachable = 0, ways = 0;
      for (int i = 0; i < n; i++)
        for (Edge &e: tree[i])
          if (level[i] < level[e.to])
            ways += (lli)(subtreeSize[e.to]) * (n - subtreeSize[e.to]);
    }
    else if (groupInfos.size() == 1)
    {
      DEBUG2 { printf("\tkind 2\n"); fflush(stdout); }
      lli sz = groupInfos[0].groupSize;
      maxReachable = sz * (sz - 1) >> 1LL, ways = 0;
      // Any combination is valid
      if (sz == n)
      {
        for (int i = 0; i < n; i++)
          for (Edge &e: tree[i])
            if (level[i] < level[e.to])
              ways += (lli)(subtreeSize[e.to]) * (n - subtreeSize[e.to]);
      }
      else
      {
        for (int i = 0; i < n; i++)
          for (Edge &e: tree[i])
            if (level[i] < level[e.to] && (s[i] == '#' || s[e.to] == '#'))
              ways += (lli)(subtreeSize[e.to]) * (n - subtreeSize[e.to]);
        ways += (lli)(sz - 1) * (sz - 1);
      }
      // ways >>= 1LL;
    }
    else if (groupInfos[0].groupSize != groupInfos[1].groupSize)
    {
      DEBUG2 { printf("\tkind 3 - %d %d\n", groupInfos[0].groupSize, groupInfos[1].groupSize); fflush(stdout); }
      lli sz = groupInfos[0].groupSize + groupInfos[1].groupSize;
      lli comb = (lli)groupInfos[0].groupSize * groupInfos[1].groupSize;
      maxReachable = sz * (sz - 1) >> 1LL, ways = 0;

      kind3FixInfectedEdges(groupInfos[0], groupInfos[1].groupSize);
      for (int i = 1; i < groupInfos.size(); i++)
      {
        if (groupInfos[i].groupSize != groupInfos[1].groupSize)
        {
          DEBUG2 printf("\t\tthere were %d groups\n", i);
          // Add the left-over groups
          for (int j = 2; j < groupInfos.size(); j++)
          {
            sz = groupInfos[j].groupSize;
            maxReachable += sz * (sz - 1) >> 1LL;
          }
          break;
        }

        ways += (lli)groupInfos[i].infectedEdges * comb;
      }
    }
    else
    {
      DEBUG2 { printf("\tkind 4\n"); fflush(stdout); }

      lli sz = 2LL * groupInfos[0].groupSize;
      maxReachable = sz * (sz - 1) >> 1LL, ways = 0;
      lli comb = (lli)groupInfos[0].groupSize * groupInfos[0].groupSize;

      dfsBigGroups();
      lli infectedEdgesSum = dfsSumInfectedEdges();

      for (int i = 0; i < groupInfos.size(); i++)
      {
        if (groupInfos[i].groupSize != groupInfos[0].groupSize)
        {
          // Add the left-over groups
          for (int j = 2; j < groupInfos.size(); j++)
          {
            sz = groupInfos[j].groupSize;
            maxReachable += sz * (sz - 1) >> 1LL;
          }
          break;
        }
      }

      // infectedEdgesSum >>= 1LL;
      ways = comb * infectedEdgesSum;
      DEBUG2 printf("\t\t%lld %lld\n", comb, infectedEdgesSum);
      // 23 24 25 (remember to subtract 1)
      // 239 240 241 (remember to subtract 1)
      // DEBUG2
      // for (int i = 0; i < 3; i++)
      //   for (int j = 0; j < 3; j++)
      // printf("\t\t\tdist(%d, %d) - %d\n", 10, 21, dist(9, 20).second);
    }

    printf("Case #%d: %lld %lld\n", tt, maxReachable, ways); fflush(stdout);
    DEBUG2 printf("\n");
  }
  return 0;
}