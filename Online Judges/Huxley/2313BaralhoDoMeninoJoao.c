#include <stdio.h>
#include <string.h>

typedef struct card
{
  char name[41], nextCard[41];
  int hSize, habilities[51];
} card_t;

void swap(card_t *a, card_t *b)
{
  card_t aux = *a;
  *a = *b;
  *b = aux;
}

void sort(card_t cards[], int n)
{
  int i, j;
  for (i = 0; i < n; i ++)
    for (j = i + 1; j < n; j ++)
      if (strcmp(cards[i].name, cards[j].name) > 0)
        swap(&cards[i], &cards[j]);
}

int getIndex(card_t cards[], char name[])
{
  int i = 0;
  while (strcmp(cards[i].name, name)) i ++;
  return(i);
}

int main()
{
  int n, i, j; scanf("%d", &n);
  card_t cards[n];
  for (i = 0; i < n; i ++)
  {
    scanf("\n%[^\n]", cards[i].name);
    scanf("%d", &cards[i].hSize);
    for (j = 0; j < cards[i].hSize; j ++)
      scanf("%d", &cards[i].habilities[j]);
    scanf("\n%[^\n]", cards[i].nextCard);
  }
  sort(cards, n);

  char name[41]; scanf("\n%[^\n]", name);
  int pos = getIndex(cards, name), at = 1;
  printf("%d\n%d\n", pos, cards[pos].habilities[at - 1]);
  for (i = getIndex(cards, cards[pos].nextCard); i != pos; i = getIndex(cards, cards[i].nextCard), at ++)
    printf("%d\n%d\n", i, cards[i].habilities[at % cards[i].hSize]);

  return(0);
}
