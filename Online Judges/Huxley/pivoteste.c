
#include <stdio.h>

int c = 0;

void swap(long int *a, long int *b)
{
  long int aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

int choose_pivor(long int p[], int from, int to, long int x[], int *lugar)
{
  long int media = 0, FROM2, divi = 0, aux, dist, piv, onde;
  if (to < from)
  {
    aux = to;
    to = from;
    from = aux;
  }
  FROM2 = from;
  while (FROM2 <= to)
  {
    media += x[FROM2];
    FROM2 ++;
    divi ++;
  }
  media /= divi;
  dist = abs(media - x[from]);
  piv = x[from];
  onde = from;
  while (from <= to)
  {
    if (dist >= abs(media - x[from]))
    {
      if (dist == abs(media - x[from]))
      {
        if (x[from] < piv)
        {
          dist = abs(media - x[from]);
          piv = x[from];
          onde = from;
        }
      }
      else
      {
        dist = abs(media - x[from]);
        piv = x[from];
        onde = from;
      }
    }
    from ++;
  }
  p[c] = piv;
  printf("%ld~%ld~%d\n", media, p[c], *lugar);
  //c ++;
  return(onde);
}

int partition(long int vetor[], int left, int right, int who) {
  int i;
  for (i=left; i<right; ++i) {
    if (vetor[i] <= who) {
      swap(&vetor[i], &vetor[left]);
      left ++;
    }
  }
  return left - 1;
}

void quicksort(long int num[], int first, int last, long int pivor[], int posi)
{
  if (first >= last) return;

  int middle = partition(num, first + 1, last, num[first]);//choose_pivor(pivor, first, last, num, &posi);
  swap(&num[middle], &num[first]);
  int midpoint = choose_pivor(pivor, first, last, num, &posi);//partition(num, first + 1, last, num[first]);
  swap(&num[last], &num[midpoint]);
  quicksort(num, first, midpoint, pivor, posi);
  quicksort(num, midpoint + 1, last, pivor, posi);
}
int main()
{
  long int tam, seed, a, c, m, put;
  while (scanf("%ld %ld %ld %ld %ld", &tam, &seed, &a, &c, &m) != EOF)
  {
    long int array[tam], pivor[tam];
    array[0] = seed;
    for (put = 1; put < tam; put ++)
    {
      array[put] = (a * array[put - 1] + c) % m;
    }
    quicksort(array, 0, tam - 1, pivor, 0);
    for (put = 0; put < tam; put ++)
    {
      printf("%ld ", pivor[put]);
    }
    printf("\n");
    for (put = 0; put < tam; put ++)
    {
      printf("%ld ", array[put]);
    }
    printf("\n");
  }
  /*for (put = 0; put < tam; put ++)
  {
    printf("%ld\n", pivor[put]);
  }*/
  return(0);
}
