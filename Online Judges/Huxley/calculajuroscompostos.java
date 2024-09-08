import static java.lang.Math.pow;
import java.text.NumberFormat;
import java.util.Scanner;

public class HuxleyCode
{
  public static void main(String[] args)
  {
    Scanner entrada = new Scanner(System.in);

    int meses = entrada.nextInt();
    double taxa = entrada.nextDouble();
    double valor = entrada.nextDouble();
    double respota = valor * pow((1 + taxa), meses);

    entrada.close();

    NumberFormat nf = NumberFormat.getNumberInstance();
    nf.setMaximumFractionDigits(2);
    nf.setMinimumFractionDigits(2);
    System.out.println(nf.format(respota));
  }
}
