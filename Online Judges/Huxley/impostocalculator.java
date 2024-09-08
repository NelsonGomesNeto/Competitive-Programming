import java.text.NumberFormat;
import java.util.Scanner;
import java.util.Locale;

public class HuxleyCode
{
  public static void main(String[] args)
  {
  Scanner entrada = new Scanner(System.in);
  double dolar = entrada.nextDouble();
  double aliquota = entrada.nextDouble();
  double valorproduto = entrada.nextDouble();
  double valorfrete = entrada.nextDouble();
  entrada.close();

  double valorprodutoreal, valorfretereal, valortotal, importacao, icms, totalimposto, totalpagar;

  NumberFormat nf = NumberFormat.getNumberInstance();
  nf.setGroupingUsed(false);
  nf.setMaximumFractionDigits(2);
  nf.setMinimumFractionDigits(1);

  valorprodutoreal = valorproduto * dolar;
  valorfretereal = valorfrete * dolar;
  if (valorproduto >= 2500)
  {
    valortotal = (valorproduto /*SEM O FRETE! valorfrete */) * dolar;
    importacao = (valortotal * 6) / 10;
    icms = ((valortotal + importacao) * aliquota/100)/(1 - aliquota/100);
    totalimposto = icms + importacao;
    totalpagar = totalimposto + valortotal + (valorfrete * dolar);
    valortotal = valortotal + (valorfrete * dolar);

    System.out.println(nf.format(dolar) + "\n" + nf.format(valorprodutoreal) + "\n" +
    nf.format(valorfretereal) + "\n" + nf.format(valortotal) + "\n" + nf.format(importacao) + "\n" +
    nf.format(icms) + "\n" + nf.format(totalimposto) + "\n" + nf.format(totalpagar) + "\n" + "Impostos calculados sem o frete");

    /*printf("%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\nImpostos calculados sem o frete\n",
    dolar, valorprodutoreal, valorfretereal,
    valortotal, importacao, ICMS, totalimposto, totalpagar);*/
  }
  else
  {
    valortotal = (valorproduto + valorfrete) * dolar;
    importacao = (valortotal * 6) / 10;
    icms = ((valortotal + importacao) * aliquota/100)/(1 - aliquota/100);
    totalimposto = icms + importacao;
    totalpagar = totalimposto + valortotal;

    System.out.println(nf.format(dolar) + "\n" + nf.format(valorprodutoreal) + "\n" +
    nf.format(valorfretereal) + "\n" + nf.format(valortotal) + "\n" + nf.format(importacao) + "\n" +
    nf.format(icms) + "\n" + nf.format(totalimposto) + "\n" + nf.format(totalpagar) + "\n" + "Impostos calculados com o frete");

    /*printf("%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\n%.2LF\nImpostos calculados com o frete\n",
    dolar, valorprodutoreal, valorfretereal,
    valortotal, importacao, icms, totalimposto, totalpagar);*/
  }
  }
}
