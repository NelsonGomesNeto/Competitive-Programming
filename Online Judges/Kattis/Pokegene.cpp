#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

/* Tutorial:
  There are various ways to solve this problem, but I chose LCA + Trie
  Build a Trie with all genes
  For each query:
    sort the trainer's genes
    each group like [i, i + l - 1] will contribute to the sum with the biggest
    prefix that is unique (maxPrefix). So, we must look at (i - 1, i)'s prefix
    (prevPrefix) and (i + l - 1, i + l) prefix (nextPrefix). We can't use
    prevPrefix neither nextPrefix, so:
      ans += max(maxPrefix - max(prevPrefix, nextPrefix), 0)
    You can find all those prefixes using LCA on the Trie's tree.
*/

const int maxN = 2e5, maxNodes = 4e5, maxLog = ceil(log2(4e5)); int n, q, k, l, logn;
pair<string, int> genes[maxN];
int idMap[maxN], geneInTrieId[maxN];
int level[maxNodes], ancestor[maxNodes][maxLog], logDP[maxNodes + 1], t;

struct Trie
{
  int id;
  Trie *letters[26];
};
Trie *root;
Trie *newTrie()
{
  Trie *temp = (Trie*) malloc(sizeof(Trie));
  temp->id = t ++;
  for (int i = 0; i < 26; i ++) temp->letters[i] = NULL;
  return(temp);
}
void insert(string &s)
{
  Trie *curr = root;
  for (int i = 0; i < s.size(); i ++)
  {
    if (curr->letters[s[i] - 'a'] == NULL)
      curr->letters[s[i] - 'a'] = newTrie();
    curr = curr->letters[s[i] - 'a'];
  }
}
void printSpaces(int spaces) { while (spaces --) printf(" "); }
void dfs(Trie *curr = root, int depth = 0)
{
  if (curr == NULL) return;
  for (int i = 0; i < 26; i ++)
    if (curr->letters[i] != NULL)
    {
      DEBUG { printSpaces(depth*2); printf("%c\n", 'a' + i); }
      level[curr->letters[i]->id] = level[curr->id] + 1;
      ancestor[curr->letters[i]->id][0] = curr->id;
      dfs(curr->letters[i], depth + 1);
    }
}
void build()
{
  level[0] = ancestor[0][0] = 0; dfs();
  for (int i = 1; i < logn; i ++)
    for (int u = 0, end = t; u < end; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
      u = ancestor[u][i];
  if (u == v) return(u);
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return(ancestor[u][0]);
}

int main()
{
  for (int i = 2; i <= maxNodes; i ++) logDP[i] = logDP[i >> 1] + 1;
  scanf("%d %d", &n, &q);
  root = newTrie();
  for (int i = 0; i < n; i ++)
  {
    cin >> genes[i].first;
    genes[i].second = i;
  }
  sort(genes, genes+n);
  for (int i = 0; i < n; i ++)
  {
    idMap[genes[i].second] = i;
    insert(genes[i].first);
    geneInTrieId[genes[i].second] = t - 1;
  }
  logn = ceil(log2(t));
  build();

  while (q --)
  {
    scanf("%d %d", &k, &l);
    pair<int, int> trainer[k];
    for (int i = 0, g; i < k; i ++)
    {
      scanf("%d", &g);
      trainer[i] = {idMap[g - 1], geneInTrieId[g - 1]};
    }
    sort(trainer, trainer+k);
    int ans = 0;
    for (int i = 0; i <= k - l; i ++)
    {
      int maxPrefix = level[LCA(trainer[i].second, trainer[i + l - 1].second)];
      int prevPrefix = 0, nextPrefix = 0;
      if (i) prevPrefix = level[LCA(trainer[i].second, trainer[i - 1].second)];
      if (i < k - l) nextPrefix = level[LCA(trainer[i + l - 1].second, trainer[i + l].second)];
      ans += max(maxPrefix - max(prevPrefix, nextPrefix), 0);
    }
    printf("%d\n", ans);
  }

  return(0);
}