#include <stdio.h>

void printMatrix(int size, char mat[][size + 1])
{
  int i, j;
  for (i = 0; i < size; i ++)
  {
    for (j = 0; j < size; j ++)
      printf("%c", mat[i][j]);
    printf("\n");
  }
}

void zoom(int size, int li, int hi, int lj, int hj, char image[][size + 1])
{
  //printf("Entered\n"); printMatrix(size, image);
  if (li == hi - 1 && lj == hj - 1)
  {
    printf("0\n"); return;
  }

  int midi = (li + hi) / 2, midj = (lj + hj) / 2, i, j;
  for (i = li; i < hi; i ++)
    for (j = lj; j < hj; j ++)
      if (image[i][j] == '*')
      {
        if (i < midi && j >= midj)
        {
          printf("1");
          zoom(size, li, midi, midj, hj, image);
        }
        if (i < midi && j < midj)
        {
          printf("2");
          zoom(size, li, midi, lj, midj, image);
        }
        if (i >= midi && j < midj)
        {
          printf("3");
          zoom(size, midi, hi, lj, midj, image);
        }
        if (i >= midi && j >= midj)
        {
          printf("4");
          zoom(size, midi, hi, midj, hj, image);
        }
      }
}

int main()
{
  int size; scanf("%d", &size);
  char image[size][size + 1]; int i, j;
  for (i = 0; i < size; i ++)
  {
    getchar();
    for (j = 0; j < size; j ++)
      scanf("%c", &image[i][j]);
  }

  zoom(size, 0, size, 0, size, image);

  return(0);
}