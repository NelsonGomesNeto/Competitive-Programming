#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atual;

struct candidato
{
  int ida, volta;
};

void insert(int vai[], int volta[], int pos, int go, int back)
{
  //int aux = atual;
  atual -= (pos + 1);
  if (pos == atual + pos + 1)
  {
    vai[pos] = go;
    volta[pos] = back;
  }
  else if (vai[pos] > go)
  {
    memmove(vai + pos + 1, vai + pos, sizeof(int) * (atual + 1));
    memmove(volta + pos + 1, volta + pos, sizeof(int) * (atual + 1));
    vai[pos] = go;
    volta[pos] = back;
  }
  else if (vai[pos] < go)
  {
    pos ++;
    //printf("##%d %d\n", vai[pos], volta[pos]);
    memmove(vai + pos + 1, vai + pos, sizeof(*vai) * (atual + 1));
    memmove(volta + pos + 1, volta + pos, sizeof(int) * (atual + 1));
    //printf("##%d %d\n", vai[pos], volta[pos]);
    vai[pos] = go;
    volta[pos] = back;
  }
  else if (volta[pos] > back)
  {
    memmove(vai + pos + 1, vai + pos, sizeof(int) * (atual + 1));
    memmove(volta + pos + 1, volta + pos, sizeof(int) * (atual + 1));
    volta[pos] = back;
  }
  else if (volta[pos] < back)
  {
    pos ++;
    memmove(vai + pos + 1, vai + pos, sizeof(int) * (atual + 1));
    memmove(volta + pos + 1, volta + pos, sizeof(int) * (atual + 1));
    vai[pos] = go;
    volta[pos] = back;
  }
  else
  {
    memmove(vai + pos + 1, vai + pos, sizeof(int) * (atual + 1));
    memmove(volta + pos + 1, volta + pos, sizeof(int) * (atual + 1));
    vai[pos] = go;
    volta[pos] = back;
  }
}

void remov(int vai[], int volta[], int pos)
{
  atual -= pos;
  pos ++;
  memmove(vai + pos - 1, vai + pos, sizeof(int) * (atual));
  memmove(volta + pos - 1, volta + pos, sizeof(int) * (atual));
}

int binS(int in[], int out[], int start, int end, int go, int back, char type)
{
  int mid = (end + start) / 2;
  if (end < start)
  {
    if (type == '+')
    {
      insert(in, out, mid, go, back);
      return(0);
    }
    return(0); //Não achou para remoção.
  }

  if (go < in[mid])
  {
    return(binS(in, out, start, mid - 1, go, back, type));
  }
  if (go > in[mid])
  {
    return(binS(in, out, mid + 1, end, go, back, type));
  }
  if (back < out[mid])
  {
    return(binS(in, out, start, mid - 1, go, back, type));
  }
  if (back > out[mid])
  {
    return(binS(in, out, mid + 1, end, go, back, type));
  }

  if (type == '+')
  {
    insert(in, out, mid, go, back);
  }
  else if (type == '-')
  {
    remov(in, out, mid);
    return(1);
  }
  return(0);
}

int main()
{
  int candidatos, i, j;
  while (scanf("%d", &candidatos) && candidatos != 0)
  {
    int ok = 0, solved = 1, travels = 0;
    int *go = calloc(candidatos, sizeof(int));
    int *back = calloc(candidatos, sizeof(int));
    int ida, volta, to;
    for (i = 0; i < candidatos - ok; i ++) //Leitura
    {
      scanf("%d %d", &ida, &volta);
      if (i >= (candidatos / 2) + 1)
      {
        continue;
      }
      if (i == 0)
      {
        go[i] = ida;
        back[i] = volta;
      }
      else
      {
        atual = i;
        if (binS(go, back, 0, i + 1, volta, ida, '-'))
        {
          ok += 2;
          i -= 2;
        }
        else
        {
          binS(go, back, 0, i, ida, volta, '+');
        }
      }
    }
    if (candidatos & 1)
    {
      printf("NO\n");
      continue;
    }
    for (i = 0; i < candidatos - ok; i ++)
    {
      //Sim, trocado mesmo!
      atual = candidatos;
      if (binS(go, back, 0, candidatos - 1 - ok, back[i], go[i], '-'))
      {
        remov(go, back, i);
        ok += 2;
        i --;
      }
      else
      {
        break;
      }
    }
    if (ok == candidatos)
    {
      printf("YES\n");
    }
    else
    {
      printf("NO\n");
    }
    free(go); free(back);
  }
  return(0);
}
