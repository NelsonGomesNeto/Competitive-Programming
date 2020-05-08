#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLen = 201; int n;
char ss[maxLen];
string numbers[maxN];

void spaces(int s) { while (s--) printf(" "); }

struct Trie;
Trie* newTrie();

struct Trie
{
  Trie **tries = NULL;
  bool endOfWord = false;

  int dfs()
  {
    int ans = 0;
    for (int i = 0; i < 10; i++)
    {
      DEBUG printf("%d %p\n", i, this->tries[i]);
      if (tries[i] != NULL)
        ans += 1 + tries[i]->dfs();
    }
    return ans;
  }
  void destroy()
  {
    if (tries == NULL) return;
    for (int i = 0; i < 10; i++)
      if (tries[i] != NULL)
      {
        tries[i]->destroy();
        free(tries[i]);
      }
    free(tries);
  }
};

Trie* newTrie()
{
  Trie *temp = (Trie*)malloc(sizeof(Trie));
  temp->tries = (Trie**)malloc(10*sizeof(Trie*));
  for (int i = 0; i < 10; i++) temp->tries[i] = NULL;
  temp->endOfWord = false;
  return temp;
}

Trie *trie = newTrie();

void addWord(string &word, Trie *curr = trie)
{
  for (int i = 0; i < word.size(); i++)
  {
    if (curr->tries[word[i] - '0'] == NULL) curr->tries[word[i] - '0'] = newTrie();
    curr = curr->tries[word[i] - '0'];
  }
  curr->endOfWord = true;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    trie = newTrie();
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      numbers[i] = string(ss);
    }
    sort(numbers, numbers+n);
    for (int i = 0; i < n; i++)
      addWord(numbers[i]);

    int ans = numbers[0].size()*n - trie->dfs();
    printf("%d\n", ans);

    // trie->destroy();
  }
  return 0;
}