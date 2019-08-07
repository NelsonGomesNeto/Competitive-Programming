#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1500; int n, k;
char s[maxN + 1];
int a[256];

struct Trie
{
  Trie **nodes;
};
Trie *trie;

Trie* newTrie()
{
  Trie *temp = (Trie*) malloc(sizeof(Trie));
  temp->nodes = (Trie**) malloc(26 * sizeof(Trie*));
  for (int i = 0; i < 26; i ++) temp->nodes[i] = NULL;
  return(temp);
}

int main()
{
  trie = newTrie();

  scanf("%s", s); n = strlen(s);
  for (int i = 'a'; i <= 'z'; i ++) { scanf("%1d", &a[i]); a[i] = 1 - a[i]; }
  scanf("%d", &k);

  int total = 0;
  for (int i = 0; i < n; i ++)
  {
    Trie *current = trie; int bad = 0;
    for (int j = i; j < n; j ++)
    {
      bad += a[s[j]]; if (bad > k) break;
      if (current->nodes[s[j] - 'a'] == NULL)
        current->nodes[s[j] - 'a'] = newTrie(), total ++;
      current = current->nodes[s[j] - 'a'];
    }
  }
  printf("%d\n", total);

  return(0);
}