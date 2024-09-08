#include <stdio.h>

int main()
{
  int n, dificuldade[n], repeat, desconto = 3;
  float preco[n];
  scanf("%i", &n);
  for (repeat = 0; repeat < n; repeat ++)
  {
    scanf("%i %f", &dificuldade[repeat], &preco[repeat]);
    if (preco[repeat] > 45)
    {
      if (dificuldade[repeat] == 0)
      {
        for (desconto = 0; desconto < 3; desconto ++)
        {
          if (preco[repeat] <= 100)
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.125);
          }
          else
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.25);
          }
        }
      }
      if (dificuldade[repeat] == 1)
      {
        for (desconto = 0; desconto < 3; desconto ++)
        {
          if (preco[repeat] <= 100)
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.10);
          }
          else
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.20);
          }
        }
      }
      if (dificuldade[repeat] == 2)
      {
        for (desconto = 0; desconto < 3; desconto ++)
        {
          if (preco[repeat] <= 100)
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.09);
          }
          else
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.18);
          }
        }
      }
      if (dificuldade[repeat] == 3)
      {
        for (desconto = 0; desconto < 3; desconto ++)
        {
          if (preco[repeat] <= 100)
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.075);
          }
          else
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.15);
          }
        }
      }
      if (dificuldade[repeat] == 4)
      {
        for (desconto = 0; desconto < 3; desconto ++)
        {
          if (preco[repeat] <= 100)
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.06);
          }
          else
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.12);
          }
        }
      }
      if (dificuldade[repeat] == 5)
      {
        for (desconto = 0; desconto < 3; desconto ++)
        {
          if (preco[repeat] <= 100)
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.05);
          }
          else
          {
            preco[repeat] = preco[repeat] - (preco[repeat] * 0.10);
          }
        }
      }
      if (preco[repeat] < 45)
      {
        preco[repeat] = 45;
      }
    }
  }
  for (repeat = 0; repeat < n; repeat ++)
  {
    printf("Jogo[%i] = R$%.2f\n", repeat, preco[repeat]);
  }
  return(0);
}
