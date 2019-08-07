#include <stdio.h>
#include <string.h>
#include <math.h>
//TESTE AGORA!!!!!!
int main()
{
  long double possivel[100000], total = 1; char word[1000000], simbolos[1000000], num[99999], comp[99999];
  printf("%lf\n", pow(10,100));
  scanf("%s", simbolos);
  scanf("%s", word);  //printf("%d~%d\n", atoi(word),atoi(simbolos));
  int i, j, zero, sol = 0, we;
  for (i = strlen(word) - 1; i >= 0; i --)
  {
    printf("%c\n", word[i]);
    for (zero = 0; zero <= 99999; zero ++)
    {
      num[zero] = ' ';
    }
    num[strlen(simbolos) - 1] = word[i];
    j = strlen(simbolos) - 1;
    if (word[i] == '0')
    {
      j --;
      i --;
      //num[j] = word[i];
      possivel[sol] = 1;
      while (word[i] == '0')
      {
        j --;
        i --;
        num[j] = word[i];
        if (atoi(num) >= atoi(simbolos))
        {
          possivel[sol] = 0;
        }
        //possivel[sol] ++;
      }
    }
    else
    {
      //num[0] = word[i];
      possivel[sol] = 0;
      we = i;
      while (atoi(num) <= atoi(simbolos) && i >= 0 && j >= 0)
      {
        //i --;
        if (we == 0)
        {
          possivel[sol] ++;
          break;
        }
        possivel[sol] ++;
        j --;
        we --;
        num[j] = word[we];
        if (word[we] == '0')
        {
          break;
        }
        printf("%d~%Lf\n", atoi(num), possivel[sol]);
      }
    }
    //printf("%d ### %d\n", atoi(num), atoi(simbolos));
    sol ++;
    //total *= possivel;
    //total = ((long long int)total) % 1000000007;
    //printf("%.0Lf####\n", possivel);
  }
  for (i = 0; i < sol - 1; i ++)
  {
    if (possivel[i] > 1 && possivel[i + 1] > 1)
    {
      total *= (possivel[i] * possivel[i + 1]) - 1;
      i ++;
    }
    else
    {
      total *= possivel[i];
      total = ((long long int)total) % 1000000007;
    }
  }
  total *= possivel[i];
  printf("%Ld\n", ((long long int)total) % 1000000007);
  return(0);
}
/*102
102
98349012840214921994021492142910421842148218394012894023840785921357293057239472394792307392072930847932014798201759129781423794021374092314972391048273091487392104793248732
85325441*/
