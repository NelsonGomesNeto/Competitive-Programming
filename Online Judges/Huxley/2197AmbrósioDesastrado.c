#include <stdio.h>

typedef struct Piece
{
  int id; char letter;
} Piece;

void swap(Piece *a, Piece *b)
{
  Piece aux = *a;
  *a = *b;
  *b = aux;
}

void sort(int n, Piece pieces[])
{
  int i, j;
  for (i = 0; i < n - 1; i ++)
    for (j = i + 1; j < n; j ++)
      if (pieces[i].id > pieces[j].id)
        swap(&pieces[i], &pieces[j]);
}

int main()
{
  int n; scanf("%d", &n);
  Piece pieces[n];
  int i; for (i = 0; i < n; i ++) scanf("%d %c", &pieces[i].id, &pieces[i].letter);
  sort(n, pieces);
  for (i = 0; i < n; i ++) printf("%c", pieces[i].letter);
  printf("\n");
  return(0);
}