#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = 20; int n;
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

int main()
{
  scanf("%s", str); n = strlen(str);

  for (int i = 0; i < n; i ++) rnk[i][0] = str[i] - 'a';

  int k;
  for (k = 1; (1 << (k - 1)) < n; k ++)
  {
    for (int i = 0; i < n; i ++)
      nodes[i] = {rnk[i][k - 1], i + (1 << (k - 1)) < n ? rnk[i + (1 << (k - 1))][k - 1] : -1, i};
    sort(nodes, nodes+n);
    // sort(nodes, nodes+n); reverse(nodes, nodes+n);
    for (int i = 0; i < n; i ++)
      rnk[nodes[i].index][k] = (i && nodes[i].lo == nodes[i - 1].lo && nodes[i].hi == nodes[i - 1].hi) ? rnk[nodes[i - 1].index][k] : i;
  }
  k --;
  print();
  int ranking[maxN];
  for (int i = 0; i < n; i ++)
    ranking[rnk[i][k]] = i;
  for (int i = 0; i < n; i ++)
    printf("%d %s\n", ranking[i], str+ranking[i]);

  return(0);
}