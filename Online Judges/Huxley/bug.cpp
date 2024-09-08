/*
 * Solu��o do problema 'Altas aventuras' (OBI 2010 - N�vel 2, Fase 2)
 *
 * Maur�cio de Lemos Rodrigues Collares Neto (<mauricioc@gmail.com>)
 */

#include <cstdio>
#include <cstring>
#include <cmath>

long long C[50001][31];

int main()
{
    int n, k, ret = 0;

    /*
      Tentemos estabelecer uma f�rmula recursiva para o maior valor de
      N tal que T testes e K bal�es determinam unicamente o m�ximo que
      podemos encher um. Chamemos esse valor de A[T][K]. Se tentarmos
      estourar um bal�o no valor x, podem acontecer duas coisas:

      1) Ele pode n�o estourar. Tesse caso, temos que verificar a
      regi�o [x+1, A[T][K]] tendo T-1 testes e K bal�es.

      2) Ele pode estourar. Nesse caso, temos que verificar a regi�o
      [1, x-1] tendo T-1 testes e K-1 bal�es (pois um acabou de ser
      estourado).

      Ora, o maior tamanho da regi�o 1 � dado por A[T-1][K] (note que
      apenas o tamanho da regi�o importa; o valor incial n�o �
      importante), e o maior tamanho da regi�o 2 � dado por
      A[T-1][K].

      Conclui-se que o maior valor poss�vel de ser testado com T
      testes e K bal�es � dado por A[T-1][K] + A[T-1][K-1] + 1, pois
      este valor maximiza o tamanho das duas regi�es. Note que as duas
      primeiras parcelas correspondem aos tamanhos m�ximos das regi�es
      1 e 2, e a terceira parcela corresponde ao fato de que n�o
      precisamos mais testar a posi��o x. Com esse valor, o primeiro
      teste ser� feito em x = A[T-1][K] + 1.

      Isto j� nos d� uma solu��o usando programa��o din�mica,
      suficiente para ganhar 40 pontos. Dado o limite em T, n�o
      poderemos calcular todos os valores para conseguir 100
      pontos. Um dos jeitos poss�veis de contornar isso � resolver a
      recorr�ncia. Para isso, podemos notar que a recorr�ncia � quase
      a recorr�ncia dada pela rela��o de Stiefel: Binomial[T][K] =
      Binomial[T-1][K] + Binomial[T-1][K-1]. O "+1", atrapalha, no
      entanto, ent�o teremos que remover ele de um jeito ou de outro.

      O primeiro impulso � remover o 1 definindo uma sequ�ncia
      auxiliar B[T][K] = A[T][K] - 1, mas isso n�o funciona, visto que
      a recorr�ncia original possui um termo do lado esquerdo e dois
      do lado direito (escreva a recorr�ncia de B[T][K] para ver o que
      acontece!). Depois de algumas tentativas, podemos pensar em
      subtrair um valor da sequ�ncia de outro valor da sequ�ncia para
      contornar esse problema. Definindo C[T][K] = A[T][K+1] -
      A[T][K], temos:

      C[T][K] = A[T][K+1] - A[T][K] =
      A[T-1][K+1] + A[T-1][K] + 1 - A[T-1][K] - A[T-1][K-1] - 1 =
      (A[T-1][K+1] - A[T-1][K]) + (A[T-1][K] + A[T-1][K-1]) =
      C[T-1][K] + C[T-1][K-1]

      Sucesso! Esta � exatamente a rela��o de Stiefel, s� precisamos
      conferir os valores iniciais agora. A[0][i] � igual a zero para
      todo i, pois n�o podemos concluir nada com zero testes;
      portanto, C[0][i] tamb�m � igual a zero pra todo i. Mas
      Binomial[0][0] = 1. Temos mais um problema a contornar. Dessa
      vez, vamos tentar roubar um pouco: Binomial[0][0] �, de fato, 1,
      mas Binomial[0][i] � zero se i >= 1. Ent�o tentemos ver se
      C[0][i] = Binomial[0][i+1].

      Ora, � f�cil de ver que a mudan�a no termo da direita n�o afeta
      a rela��o de Stiefel, e agora os valores de C[0][i] concordam
      sempre! Segue-se que, de fato, C[T][K] = Binomial[T][K+1] pra
      todo T e todo K n�o negativos. Mas o que isso implica para
      A[T][K]?

      A[T][K] = (A[T][K] - A[T][K-1]) + (A[T][K-1] + A[T][K-2]) +
      ... + (A[T][1] - A[T][0]) + A[T][0]
      = C[T][K-1] + C[T][K-2] + ... + C[T][0] + A[T][0]
      = C[T][K-1] + C[T][K-2] + ... + C[T][0], pois A[T][0] = 0.
      = Binomial[T][K] + Binomial[T][K-1] + ... +
      Binomial[T][1].

      Temos ent�o uma f�rmula bonita para A[T][K]. Voltemos para o
      nosso problema: Queremos saber qual o menor n�mero de testes que
      precisamos para determinar o valor m�nimo N de estouro. Ou
      seja, queremos saber o menor T tal que A[T][K] >= N (se conven�a
      disso a partir da defini��o de A[T][K] antes de
      continuar).

      Se K = 1, A[T][K] � igual a Binomial[T][1] = T, donde a resposta
      � N, de imediato. J� se K = 2, ent�o A[T][K] = T*(T+1)/2, e
      portanto T = 5*10^4 j� � mais que suficiente para fazer A[T][K]
      ser maior que o maior valor poss�vel de N, que � 10^9. Podemos
      ent�o tentar cada valor de T em sequ�ncia, mas a� surge um outro
      problema: Como calcular Binomial[T][K] quando T e K s�o grandes?
      Poder�amos notar que, nesse caso, o valor do binomial vai passar
      rapidamente de 10^9, mas vamos resolver esse problema de outro
      jeito.

      Note que ter mais de 30 bal�es nunca � vantagem: Se fosse,
      ter�amos que fazer mais de 30 testes; do contr�rio, pelo menos
      um bal�o ficaria parado. Mas, com 30 testes e 30 bal�es, j�
      temos A[30][30] = 2^30 - 1 > 10^9, lembrando que a soma da
      n-�sima linha do tri�ngulo de Pascal � 2^n, donde podemos supor
      que K � menor ou igual a 30 (outra maneira de ver isso � que,
      com mais de 30 bal�es e 30 testes, temos bal�es suficientes para
      fazer uma busca bin�ria direta, sem se preocupar com o fim do
      estoque de bal�es). Nosso problema est� resolvido.

      A solu��o abaixo precomputa os binomiais necess�rios
      (trabalhando com long long, mas sem preocupar com overflow: se
      algum binomial estourar, � f�cil de ver que a soma dos binomiais
      ir� chegar em N muito antes de tentarmos som�-lo a nossa
      resposta) e depois faz uma busca linear em T. O caso K == 1 �
      tratado em especial, como acima.
    */

    memset(C, 0, sizeof C);
    C[0][0] = 1;
    for(int i = 1; i <= 50000; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= 30; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    while (~scanf("%d %d", &n, &k))
    {
      if(k == 1)
          printf("%d\n", n);
      else {
          if(k > 30)
              k = 30;

          bool skip = false;
          for(int i = 1; !skip; i++) {
              long long soma = 0;
              for(int j = 1; j <= k && !skip; j++) {
                  soma += C[i][j];
                  if(soma >= n) {
                      printf("%d\n", i);
                      skip = true;
                      break;
                  }
              }
          }
      }
    }
}
