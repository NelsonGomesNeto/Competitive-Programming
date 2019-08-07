#include <stdio.h>

int main()
{
  int cred, semestre; scanf("%i", &cred); cred = 260 - cred;
  semestre = cred / 24;
  printf("%i\n", semestre);
}
