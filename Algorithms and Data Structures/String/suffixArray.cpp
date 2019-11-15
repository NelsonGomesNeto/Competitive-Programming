#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 1e6, maxLog = 20; int n;
char str[maxN + 1];
int rnk[maxN][maxLog];
struct Node
{
  int lo, hi, index;
  bool operator<(const Node &no) const
  {
    return(lo < no.lo || (lo == no.lo && hi < no.hi));
  }
};
Node nodes[maxN];
void print()
{
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < maxLog; j ++)
      printf("%4d%c", rnk[i][j], j < maxLog - 1 ? ' ' : '\n');
}

int aux[maxN + 1];
vector<Node> aux2[maxN + 1], aux3[maxN + 1];
void countSort(Node arr[], int sz)
{
  for (int i = 0, end = max(26, sz); i <= end; i ++)
    aux2[i].clear();
  for (int i = 0; i < sz; i ++)
    aux2[arr[i].lo].push_back(arr[i]);
  for (int i = 0, end = max(26, sz); i <= end; i ++)
    if (!aux2[i].empty())
      sort(aux2[i].begin(), aux2[i].end());
  for (int i = 0, j = 0, end = max(26, sz); i <= end; i ++)
    for (Node &a: aux2[i])
      arr[j ++] = a;
}

int main()
{
  scanf("%s", str); n = strlen(str);

  for (int i = 0; i < n; i ++) rnk[i][0] = str[i] - 'a';

  int k;
  for (k = 0; (1 << k) < n; k ++)
  {
    for (int i = 0; i < n; i ++)
      nodes[i] = {rnk[i][k], i + (1 << k) < n ? rnk[i + (1 << k)][k] : -1, i};
    // sort(nodes, nodes+n);
    countSort(nodes, n);
    for (int i = 0; i < n; i ++)
      rnk[nodes[i].index][k + 1] = (i && nodes[i].lo == nodes[i - 1].lo && nodes[i].hi == nodes[i - 1].hi) ? rnk[nodes[i - 1].index][k + 1] : i;
  }
  DEBUG print();
  int ranking[maxN];
  for (int i = 0; i < n; i ++)
    ranking[rnk[i][k]] = i;
  for (int i = 0; i < n; i ++)
  {
    // DEBUG printf("%d %s\n", ranking[i], str+ranking[i]);
    // else printf("%d\n", ranking[i]);
    // printf("%d\n", ranking[i]);
  }

  return(0);
}