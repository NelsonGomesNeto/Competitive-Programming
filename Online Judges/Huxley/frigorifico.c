#include <stdio.h>

int main()
{
  int bois;
  scanf("%i", &bois);
  int idBois[bois], idFat, idMagro, repeat; float peso[bois], fat, magro;
  for (repeat = 0; repeat < bois; repeat ++)
  {
    scanf("%i %f", &idBois[repeat], &peso[repeat]);
    if (repeat == 0 || peso[repeat] < magro)
    {
      magro = peso[repeat];
      idMagro = idBois[repeat];
    }
    if (repeat == 0 || peso[repeat] > fat)
    {
      fat = peso[repeat];
      idFat = idBois[repeat];
    }
  }
  printf("Gordo: id: %i peso: %.2fKg\n", idFat, fat);
  printf("Magro: id: %i peso: %.2fKg\n", idMagro, magro);
  return(0);
}
