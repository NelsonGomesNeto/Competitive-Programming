#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
struct Trie
{
  bool wordEnd; int options;
  Trie *letters[26];
};
Trie *root;
Trie *newNode()
{
  Trie *temp = (Trie*) malloc(sizeof(Trie));
  temp->wordEnd = false, temp->options = 0;
  for (int i = 0; i < 26; i ++)
    temp->letters[i] = NULL;
  return(temp);
}
void insert(char s[])
{
  Trie *curr = root;
  for (int i = 0; s[i]; i ++)
  {
    if (s[i] == '_') continue;
    if (curr->letters[s[i] - 'a'] == NULL)
      curr->letters[s[i] - 'a'] = newNode(), curr->options ++;
    curr = curr->letters[s[i] - 'a'];
  }
  curr->wordEnd = true;
}
long double dfs(Trie *curr = root, int depth = 0)
{
  // if (curr->wordEnd) printf("\t%d\n", depth);
  long double ans = curr->wordEnd ? depth : 0;
  for (int i = 0; i < 26; i ++)
    if (curr->letters[i] != NULL)
    {
      // printf("%*c - %c\n", depth, '\t', i + 'a');
      ans += dfs(curr->letters[i], depth + (depth == 0 || curr->wordEnd + curr->options > 1));
    }
  return(ans);
}
void destroy(Trie *curr = root)
{
  if (curr == NULL) return;
  for (int i = 0; i < 26; i ++)
    destroy(curr->letters[i]);
  free(curr);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    root = newNode();

    for (int i = 0; i < n; i ++)
    {
      char s[100]; scanf(" %s", s);
      insert(s);
      // printf("inserted: %s\n", s); fflush(stdout);
    }
    long double ans = dfs() / n;
    printf("%.2Lf\n", ans);

    destroy(root);
  }
  return(0);
}