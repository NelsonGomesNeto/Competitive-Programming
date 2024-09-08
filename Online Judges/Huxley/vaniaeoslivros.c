#include <stdio.h>
#include <math.h>

/*
A ideia é: (ex: livros = 222)
Pega a quantidade de dígitos (qc = 3) e acha a quantidade de dígitos com
10^(qc - 1), seguindo:
9*1 + 90*2 + 900*3 + 9000*4... E no final: + (1 * qc);
Para 100: 9 + 90*2 + 1*3 = 192;
Diminui (10^(qc - 1)) de livros: livros = 122;
Agora para cada dígito, vamos multiplicar por qc:
(100 * qc) + (20 * qc) + (2 * qc), adiciona isso na quantidade de dígitos
atual (192) e gg: livros = 222 resultará em 558 casas ^~^
*/

int main()
{
  long long int livros; scanf("%Ld", &livros);
  long long int digitos = 0;
  int quantiCasas = floor(log10(livros)) + 1;
  int qcBackUp = quantiCasas;
  int reduz = 1;
  while (reduz < quantiCasas)
  {
    digitos += (((9 * pow(10, reduz - 1))) * (reduz));
    reduz ++;
  }
  digitos += (1 * reduz);
  livros -= pow(10, quantiCasas - 1);
  while (livros > 0)
  {
    quantiCasas = floor(log10(livros));
    int atual = livros / pow(10, quantiCasas);
    digitos += (atual * pow(10, quantiCasas) * qcBackUp);
    livros %= (int) pow(10, quantiCasas);
  }
  printf("%Ld\n", digitos);
  return(0);
}