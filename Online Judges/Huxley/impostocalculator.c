#include <stdio.h>
#include <math.h>

void printFormatado(long double valor)
{
  if ((int) round(valor * 100) % 10 == 0)
  {
    printf("%.1LF\n", valor);
  }
  else
  {
    printf("%.2LF\n", valor);
  }
}

int main()
{
  long double dolar, aliquota, valorproduto, valorprodutoreal, valorfrete;
  long double valorfretereal, valortotal, importacao, ICMS, totalimposto, totalpagar;
  scanf("%LF\n%LF\n%LF\n%LF", &dolar, &aliquota, &valorproduto, &valorfrete);
  valorprodutoreal = valorproduto * dolar;
  valorfretereal = valorfrete * dolar;
  if (valorproduto >= 2500)
  {
    valortotal = (valorproduto /*SEM O FRETE! valorfrete */) * dolar;
    importacao = (valortotal * 6) / 10;
    ICMS = ((valortotal + importacao) * aliquota/100)/(1 - aliquota/100);
    totalimposto = ICMS + importacao;
    totalpagar = totalimposto + valortotal + (valorfrete * dolar);
    valortotal = valortotal + (valorfrete * dolar);
    //printf("%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\nImpostos calculados sem o frete\n",
  }
  else
  {
    valortotal = (valorproduto + valorfrete) * dolar;
    importacao = (valortotal * 6) / 10;
    ICMS = ((valortotal + importacao) * aliquota/100)/(1 - aliquota/100);
    totalimposto = ICMS + importacao;
    totalpagar = totalimposto + valortotal;
    //printf("%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\nImpostos calculados com o frete\n",
    /*dolar, valorprodutoreal, valorfretereal,
    valortotal, importacao, ICMS, totalimposto, totalpagar);*/
  }
  printFormatado(dolar);
  printFormatado(valorprodutoreal);
  printFormatado(valorfretereal);
  printFormatado(valortotal);
  printFormatado(importacao);
  printFormatado(ICMS);
  printFormatado(totalimposto);
  printFormatado(totalpagar);
  if (valorproduto >= 2500)
  {
    printf("Impostos calculados sem o frete\n");
  }
  else
  {
    printf("Impostos calculados com o frete\n");

  }
  return(0);
}
