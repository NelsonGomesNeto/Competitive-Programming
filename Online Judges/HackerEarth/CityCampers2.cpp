#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  Test cases were weak, so O(n*q) with small optimizations get's easy ACC
  O(lg*q) requires a quite hard implementation using sets
  For both of them, you will need to store a set of sizes (set of sizes + array to count
  the amount of each size; or a simple map), it's easy (you can test on previous problem)
  Using the same idea, you will also store a set of differences, where for each size, you
  will have three options:
    difference == 0, if size.count >= 2
    difference == size - prev(size)
    difference == next(size) - size
    (I think it's possible to do with only prev or next; but it was easier to implement this way)
  Now, for every merge, you will have to account for the changes into sizes's set, and
  reflect these differences into the differences's set. Be very cautious, and cover every case.

  After modifying the merge function, it will be as simples as:
  for each query:
    merge(u, v)
    print(sizes.size() == 0 ? 1 : differences.begin()->first)
*/

const int maxN = 1e5; int n, q;
int parent[maxN];
int differencesAmount[maxN + 1], sizesAmount[maxN + 1];
set<pair<int, pair<int, int>>> differences;
set<int> sizes;
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}
void eraseDifferences(int s)
{
  auto it = sizes.find(s);
  int before = it != sizes.begin() ? *prev(it) : -1, after = it != prev(sizes.end()) ? *next(it) : -1;
  if (before != -1) differences.erase({s - before, {before, s}});
  if (after != -1) differences.erase({after - s, {s, after}});
}
void eraseSize(int s, int jump)
{
  auto it = sizes.find(s);
  int before = it != sizes.begin() ? *prev(it) : -1, after = it != prev(sizes.end()) ? *next(it) : -1;
  if (before == jump) before = prev(it) != sizes.begin() ? *prev(prev(it)) : -1;
  if (after == jump) after = next(it) != prev(sizes.end()) ? *next(next(it)) : -1;
  if (before != -1 && after != -1 && before < s && after > s) differences.insert({after - before, {before, after}});
  sizes.erase(it);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);

  int su = setSize(u), sv = setSize(v);
  sizesAmount[su] --, sizesAmount[sv] --;
  // printf("\t%d: %d || %d: %d\n", su, sizesAmount[su], sv, sizesAmount[sv]);

  if (sizesAmount[su] < 2) differences.erase({0, {su, su}});
  if (sizesAmount[sv] < 2 && su != sv) differences.erase({0, {sv, sv}});
  if (!sizesAmount[su]) eraseDifferences(su);
  if (!sizesAmount[sv] && su != sv) eraseDifferences(sv);
  if (!sizesAmount[su]) eraseSize(su, !sizesAmount[sv] ? sv : -1);
  if (!sizesAmount[sv] && su != sv) eraseSize(sv, -1);

  parent[u] += parent[v];
  parent[v] = u;

  su = setSize(u);
  sizesAmount[su] ++;
  if (sizesAmount[su] > 1) differences.insert({0, {su, su}});
  if (sizesAmount[su] == 1)
  {
    sizes.insert(su);
    auto it = sizes.find(su);
    int before = it != sizes.begin() ? *prev(it) : -1, after = it != prev(sizes.end()) ? *next(it) : -1;
    if (before != -1 && after != -1) differences.erase({after - before, {before, after}});
    if (before != -1) differences.insert({su - before, {before, su}});
    if (after != -1) differences.insert({after - su, {su, after}});
  }
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &q);
  sizesAmount[1] = n, sizes.insert(1);
  differences.insert({0, {1, 1}});

  bool yes = true;
  vector<pair<int, int>> diff;
  for (int i = 0, u, v; i < q; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v);
    int minimumDifference = n;
    if (sizes.size() == 1 || sizesAmount[*prev(sizes.end())] > 1) minimumDifference = 0;
    for (auto it = sizes.begin(), end = prev(sizes.end()); it != end && minimumDifference; it ++)
    {
      if (sizesAmount[*it] > 1) minimumDifference = 0;
      minimumDifference = min(minimumDifference, *next(it) - *it);
    }
    if (minimumDifference != differences.begin()->first) yes = false, diff.push_back({minimumDifference, differences.begin()->first});
    // printf("%d\n", minimumDifference);
    // printf("\t\t%d -- %d\n", differences.begin()->first, (int) differences.size());
    printf("%d\n", sizes.size() == 1 ? 0 : differences.begin()->first);
  }
  // printf("%s\n", yes ? "YES" : "NO");
  // for (auto d: diff)
  //   printf("%d %d\n", d.first, d.second);
  // printf("%s\n", yes ? "YES" : "NO");

  return(0);
}