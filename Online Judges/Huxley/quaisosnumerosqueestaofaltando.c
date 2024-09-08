#include <stdio.h>

int main()
{
  int nums1[1000000], nums2, ler = 0, ler2 = 0, lerSononum = 0, not = 0;
  int printa, check, conta, aux;
  char line;
  while (scanf("%d%c", &nums1[ler], &line) && line != '\n')
  {
    ler ++;
  }
  while (scanf("%d", &nums2) != EOF)
  {
    for (check = 0; check <= ler; check ++)
    {
      if (nums2 == nums1[check])
      {
        nums1[check] = -3789201;
      }
    }
  }
  for (printa = 0; printa <= ler; printa ++)
  {
    for (check = printa; check <= ler; check ++)
    {
      if (nums1[printa] < nums1[check])
      {
        aux = nums1[printa];
        nums1[printa] = nums1[check];
        nums1[check] = aux;
      }
    }
  }
  for (printa = 0; printa <= ler; printa ++)
  {
    if (nums1[printa] == -3789201 && not == 0)
    {
      not = printa;
    }
  }
  for (printa = 0; printa < not - 1; printa ++)
  {
    if (nums1[printa] != -3789201)
    {
      printf("%d ", nums1[printa]);
    }
  }
  if (not > 0)
  {
    printf("%d\n", nums1[not - 1]);
  }
  else
  {
    printf("%d\n", nums1[not]);
  }
  return(0);
}
