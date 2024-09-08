#include <stdio.h>
typedef struct equacao reta;

struct equacao
{
  int a, b;
};

int main()
{
  int tests, casoAtual = 1; scanf("%d", &tests);
  for (casoAtual = 1; casoAtual <= tests; casoAtual ++)
  {
    reta r; scanf("%d %d", &r.a, &r.b); // Equação da reta

    int pos[70000]; // Posições no plano cartesiano
    int x = 0, y = 0, nums = 0, i; //x e y no plano cartesiano e o número atual
    int walk = 1, dir = 0, mult = 1; //Configurações de caracol

    //y > (r.a * x) + r.b Se der menor, está de um lado e se der maior, está do outro

    while (nums <= 65535) // Preenche para todos os números
    {
      if (dir == 0) // Movendo x
      {
        for (i = 0; i < walk; i ++, nums ++) // Movendo-se em caracol
        {
          pos[nums] = y > (r.a * x) + r.b; // Um lado ou outro lado
          if (y == (r.a * x) + r.b) //Se está sobre a linha
            nums --; //Volta um número

          x -= mult; // Move-se ao longo do plano em caracol
        }
        dir = 1; // Mudando de direção
      }
      else if (dir == 1) // Movendo y
      {
        for (i = 0; i < walk; i ++, nums ++) // Movendo-se em caracol
        {
          pos[nums] = y > (r.a * x) + r.b; //Um lado ou outro lado
          if (y == (r.a * x) + r.b) //Se está sobre a linha
            nums --; //Volta um número

          y += mult; // Move-se ao longo do plano em caracol
        }
        dir = 0; // Mudando de direção
        walk ++; mult *= -1; // Aumentando o tamanho e invertendo caracolmente
      }
    }

    int amigos, pessoaA, pessoaB;
    scanf("%d", &amigos); // Quantidade de amigos
    printf("Caso %d\n", casoAtual);
    while (amigos > 0) // Printa para cada amigo
    {
      scanf("%d %d", &pessoaA, &pessoaB); // Cada amigo
      if (pos[pessoaA] == pos[pessoaB])
      {
        printf("Mesmo lado da fronteira\n");
      }
      else
      {
        printf("Lados opostos da fronteira\n");
      }
      amigos --;
    }
  }
  return(0);
}
