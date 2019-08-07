#include <stdio.h>

int choose_pivor(int from, int to, long int x[])
{
  long int media = 0, FROM2, divi = 0, aux, dist, piv, onde;
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
  return(onde);
}
void quicksort(long int num[], int first, int last)
{
  int pivot, j, i, aux; long int temp[last - first + 10], number;
  if (first <= last)
  {
    pivot = choose_pivor(first, last, num);
    number = num[pivot];
    j = 0;
    for (i = first; i <= last; i++)
    {
      if (num[i] <= number && i!= pivot)
      {
        temp[j] = num[i];
        j ++;
      }
    }
    temp[j++] = number;
    for (i = first; i <= last; i++)
    {
      if (num[i] > number)
      {
        temp[j] = num[i];
        j ++;
      }
    }
    int posi = 0;
    for (i = first; i <= last; i++)
    {
      num[i] = temp[posi];
      posi ++;
    }
    int y, where;
    for (y = first; y <= last; y ++)
    {
      if (num[y] == number)
      {
        where = y;
      }
    }
    printf("(%ld,%d)", number, where + 1);
    quicksort(num, first, where - 1);
    quicksort(num, where + 1, last);
  }
}

int main()
{
  long int tam, seed, a, c, m, put;
  while (scanf("%ld %ld %ld %ld %ld", &tam, &seed, &a, &c, &m) != EOF)
  {
    long int array[tam];
    array[0] = seed;
    for (put = 1; put < tam; put ++)
    {
      array[put] = (a * array[put - 1] + c) % m;
    }
    quicksort(array, 0, tam - 1);
    printf("\n");
  }
  return(0);
}
