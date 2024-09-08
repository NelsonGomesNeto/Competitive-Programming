#include <stdio.h>

int main()
{
  int force, inte, dest, furt, peso;
  scanf("%i\n%i\n%i\n%i\n%i", &force, &inte, &dest, &furt, &peso);
  if ( (force > 5) && (dest > 5) && (peso > 5) )
  {
    printf("Knight\n");
  }
  else if ( (force < 5) && (inte > 5) && (furt > 5) && (peso < 5) )
  {
    printf("Mage\n");
  }
  else if ( (force > 5) && (inte > 5) && (dest > 5) && (furt > 5) && (peso < 5) )
  {
    printf("Paladin\n");
  }
  else
  {
    printf("Orc\n");
  }
  return(0);
}
