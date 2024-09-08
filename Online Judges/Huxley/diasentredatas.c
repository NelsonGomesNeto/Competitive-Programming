#include <stdio.h>

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int dI, mI, aI, dF, mF, aF, limitD, aux; long long int dias = 0;
  scanf("%d/%d/%d", &dI, &mI, &aI);
  scanf("%d/%d/%d", &dF, &mF, &aF);
  if (aI > aF)
  {
    swap(&dI, &dF);
    swap(&mI, &mF);
    swap(&aI, &aF);
  }
  else if (aI == aF)
  {
    if (mI > mF)
    {
      swap(&dI, &dF);
      swap(&mI, &mF);
      swap(&aI, &aF);
    }
    else if (mI == mF)
    {
      if (dI > dF)
      {
        swap(&dI, &dF);
        swap(&mI, &mF);
        swap(&aI, &aF);
      }
    }
  }
  while (!(dI == dF && mI == mF && aI == aF))
  {
    //printf("%02d/%02d/%d\n", dI, mI, aI);
    int bissexto = 0;
    if ((aI % 4 == 0 && aI % 100 != 0) || aI % 400 == 0)
      bissexto = 1;
    if (mI == 1 || mI == 3 || mI == 5 || mI == 7 || mI == 8 || mI == 10 || mI == 12)
      limitD = 31;
    else
    {
      if (mI == 2)
      {
        if (bissexto == 0)
          limitD = 28;
        else
          limitD = 29;
      }
      else
        limitD = 30;
    }
    if (mI == mF && aI == aF)
    {
      limitD = dF;
    }
    /*while (dI < limitD)
    {
      dI ++; dias ++;
    }*/
    dI = limitD - dI;
    dias += dI;
    if (!(mI == mF && aI == aF))
    {
      dI = 0;
      mI ++;
    }
    else
    {
      dI = dF;
    }
    if (mI > 12)
    {
      mI = 1;
      aI ++;
    }
  }
  printf("%Ld\n", dias);
  return(0);
}
