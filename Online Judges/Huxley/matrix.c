#include <stdio.h>

int main()
{
  int q1, q2, q3, q4, q5, pontos = 0;
  scanf("%i\n%i\n%i\n%i\n%i", &q1, &q2, &q3, &q4, &q5);
  if (q1 == 0)
  {
    pontos += 2;
  }
  if (q2 == 1)
  {
    pontos += 1;
  }
  if (q3 == 1)
  {
    pontos += 1;
  }
  if (q4 == 1)
  {
    pontos += 1;
  }
  if (q5 == 1)
  {
    pontos += 3;
  }
  if (pontos >= 5)
  {
    printf("A Matrix esta em todo lugar. A nossa volta. E o mundo colocado diante de seus olhos, para que nao veja a verdade. Infelizmente e impossivel dizer o que e a Matrix. Voce tem de ver por si mesmo. *Voce e sugado pelo telefone e revelado a verdade\n");
  }
  else
  {
    printf("Voce precisa entender que a maioria dessas pessoas nao estao prontas para acordar. E muitos estao tao inertes, tao dependentes do sistema que vao lutar para protege-lo\n");
  }
  return(0);
}
