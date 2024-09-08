#include <bits/stdc++.h>
#define DEBUG if(0)
#define DEBUG2 if(0)
#define DEBUG3 if (0 && tt > 6 && tt != 118) continue;
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, k;
char s[maxN + 1];
int e[maxN];
vector<int> tree[maxN];

void printTree(int u = 0, int prv = -1, int depth = 0)
{
  for (int i = 0; i < depth; i++) printf("   ");
  printf("%c%d\n", s[u], u + 1);

  for (int v: tree[u])
    if (v != prv)
      printTree(v, u, depth + 1);
}

vector<vector<int>> groups;
struct GroupInfo
{
  int groupSize, removableHallways, groupIdx;
  bool operator<(const GroupInfo &other) const
  {
    return groupSize > other.groupSize;
  }
};
vector<GroupInfo> groupInfos;
int subtreeSize[maxN], level[maxN];
int myGroupIndexes[maxN], myGroupSizes[maxN];
void createGroups(int u = 0, int prv = -1, int curr = 0)
{
  subtreeSize[u] = 1;
  if (s[u] == '*')
  {
    if (groups.size() <= curr) groups.push_back(vector<int>());
    groups[curr].push_back(u);
  }

  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1;
      if (s[v] == '*' && s[u] == '#')
      {
        groups.push_back(vector<int>());
        createGroups(v, u, groups.size() - 1);
      }
      else
        createGroups(v, u, curr);
      subtreeSize[u] += subtreeSize[v];
    }
}

void dfsFillRemovableHallways(int u, int prv, int targetSize, int removableHallways = 1)
{
  if (s[u] == '*' && s[prv] == '#' && myGroupSizes[u] == targetSize)
    groupInfos[myGroupIndexes[u]].removableHallways += removableHallways;

  for (int v: tree[u])
    if (v != prv)
      dfsFillRemovableHallways(v, u, targetSize, removableHallways + (s[v] == '#' || s[u] == '#'));
}
void fillRemovableHallways(GroupInfo &groupInfo, int targetSize)
{
  for (int u: groups[groupInfo.groupIdx])
    for (int v: tree[u])
      if (s[v] == '#')
        dfsFillRemovableHallways(v, u, targetSize);
}

/*
  #-*, *-#, #-# are potencial infected edges
  Here, in the forth case, we need to sum the removableHallways for each pair of
  group.
  Which is the same as sum the amount of times each potencial edge
  will be separating a pair of groups.

  So, for each each, we need to know how many big groups are before and after it
    removableHallwaysSum += before * after
*/
int subtreeBigGroups[maxN];
void dfsBigGroups(int u = 0, int prv = -1, bool inGroup = false)
{
  if (s[u] == '#') inGroup = false;
  if (myGroupSizes[u] == groupInfos[0].groupSize && !inGroup)
    subtreeBigGroups[u]++, inGroup = true;

  for (int v: tree[u])
    if (v != prv)
    {
      dfsBigGroups(v, u, inGroup);
      subtreeBigGroups[u] += subtreeBigGroups[v];
    }
}
lli dfsSumRemovableHallways(int u = 0, int prv = -1)
{
  lli total = 0;
  for (int v: tree[u])
    if (v != prv)
    {
      if (s[u] == '#' || s[v] == '#')
        total += (lli)subtreeBigGroups[v] * (subtreeBigGroups[0] - subtreeBigGroups[v]);
      total += dfsSumRemovableHallways(v, u);
    }
  return total;
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
      tree[i].push_back(e[i]);
      tree[e[i]].push_back(i);
    }

    DEBUG3

    DEBUG {
      printf("E: "); for (int i = 1; i < n; i++) printf("%d%c", e[i] + 1, i < n - 1 ? ' ' : '\n');
      printf("Tree:\n"); printTree();
    }

    groups.clear();
    createGroups();
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
      for (int u: groups[groupInfos[i].groupIdx])
        myGroupIndexes[u] = i, myGroupSizes[u] = groupInfos[i].groupSize;

    DEBUG {
      printf("Group infos: ");
      for (int i = 0; i < groupInfos.size(); i++)
        printf("(%d, %d)%c", groupInfos[i].groupSize, groupInfos[i].removableHallways, i < groupInfos.size() - 1 ? ' ' : '\n');
      if (groupInfos.empty()) printf("\n");
    }

    /*
      There are 4 cases:
      1: There is no group
      2: There is a single group
      3: The biggest group happens once
      4: The biggest group happens multiple times
    */
    lli sz, maxReachable, ways = 0;
    if (groupInfos.size() <= 1)
    {
      sz = groupInfos.empty() ? 0 : groupInfos[0].groupSize;

      for (int i = 0; i < n; i++)
        for (int v: tree[i])
          if (level[i] < level[v])
            if (sz == n || (sz != n && (s[i] == '#' || s[v] == '#')))
              ways += (lli)(subtreeSize[v]) * (n - subtreeSize[v]);
      if (sz != n && sz != 0)
        ways += (sz - 1) * (sz - 1);
    }
    else if (groupInfos[0].groupSize != groupInfos[1].groupSize)
    {
      sz = groupInfos[0].groupSize + groupInfos[1].groupSize;

      lli comb = (lli)groupInfos[0].groupSize * groupInfos[1].groupSize;
      fillRemovableHallways(groupInfos[0], groupInfos[1].groupSize);
      for (int i = 1; i < groupInfos.size() && groupInfos[i].groupSize == groupInfos[1].groupSize; i++)
        ways += comb * groupInfos[i].removableHallways;
    }
    else
    {
      sz = 2LL * groupInfos[0].groupSize;

      dfsBigGroups();
      lli removableHallwaysSum = dfsSumRemovableHallways();
      lli comb = (lli)groupInfos[0].groupSize * groupInfos[0].groupSize;
      ways = comb * removableHallwaysSum;
    }

    maxReachable = sz * (sz - 1) >> 1LL;
    // Add the left-over groups
    for (int j = 2; j < groupInfos.size(); j++)
    {
      sz = groupInfos[j].groupSize;
      maxReachable += sz * (sz - 1) >> 1LL;
    }

    printf("Case #%d: %lld %lld\n", tt, maxReachable, ways); fflush(stdout);
    DEBUG2 printf("\n");
  }
  return 0;
}