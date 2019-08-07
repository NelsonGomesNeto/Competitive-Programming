#include <stdio.h>

typedef struct game
{
  int grade; double price;
} game;

int higher(game a, game b)
{
  return(a.grade > b.grade || (a.grade == b.grade && a.price < b.price));
}

void printGame(game a)
{
  printf("Nota: %d\nPreco: %.2lf\n", a.grade, a.price);
}

void swap(game *a, game *b)
{
  game aux = *a;
  *a = *b;
  *b = aux;
}

void sort(int n, game games[])
{
  int i, j;
  for (i = 0; i < n - 1; i ++)
    for (j = i + 1; j < n; j ++)
      if (higher(games[j], games[i]))
        swap(&games[i], &games[j]);
}

int main()
{
  int n; scanf("%d", &n);
  game games[n]; int i;
  for (i = 0; i < n; i ++) scanf("%d %lf", &games[i].grade, &games[i].price);
  
  sort(n, games);
  for (i = 0; i < n; i ++)
  {
    printGame(games[i]);
    if (i < n - 1) printf("\n");
  }
  
  return 0;
}