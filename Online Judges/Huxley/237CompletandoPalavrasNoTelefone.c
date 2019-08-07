#include <stdio.h>
#include <stdlib.h>

typedef struct trie trie_t;

struct trie
{
  trie_t *alpha[35];
  int nodes;
};

trie_t* newTrie()
{
  trie_t *temp = (trie_t*) malloc(1 * sizeof(trie_t));
  int i;
  for (i = 0; i < 35; i ++)
    temp->alpha[i] = NULL;

  temp->nodes = 0;
  return(temp);
}

void add(trie_t *t, char s[])
{
  int i;
  trie_t *curr = t;
  for (i = 0; s[i] != '\0'; i ++)
  {
    if (curr->alpha[s[i] - 'a'] == NULL)
    {
      curr->alpha[s[i] - 'a'] = newTrie();
      curr->nodes ++;
      curr = curr->alpha[s[i] - 'a'];
    }
    else
    {
      curr = curr->alpha[s[i] - 'a'];
    }
  }
  curr->nodes ++;
}

int tryType(trie_t *t, char s[])
{
  int i, types = t->nodes == 1 ? 1 : 0;
  trie_t *curr = t;
  for (i = 0; s[i] != '\0'; i ++)
  {
    if (curr->nodes > 1)
      types ++;

    curr = curr->alpha[s[i] - 'a'];
  }
  return(types);
}

void destroy(trie_t *t)
{
  int i;
  for (i = 0; i < 35; i ++)
    if (t->alpha[i] != NULL)
      destroy(t->alpha[i]);

  free(t);
}

int main()
{
  int words;
  while (scanf("%d", &words) != EOF)
  {

    trie_t *t = newTrie();
    char string[words][81];
    int i;
    for (i = 0; i < words; i ++)
    {
      scanf(" %s", string[i]);
      add(t, string[i]);
    }

    int types = 0;
    for (i = 0; i < words; i ++)
      types += tryType(t, string[i]);

    printf("%.2lf\n", (double) types / words);
    destroy(t);
  }
  return(0);
}
