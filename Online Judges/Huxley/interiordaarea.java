import java.text.NumberFormat;
import java.util.Scanner;
import java.util.Locale;

public class HuxleyCode
{
  public static void main(String[] args)
  {
    double x = 1; double y = 1;
    double yMax; double yMin;
    Scanner entrada = new Scanner(System.in);
    x = entrada.nextDouble();
    y = entrada.nextDouble();
    while (!(x == 0 && y == 0))
    {
      yMax = 3 * x;
      yMin = x / 3;
      if (x > 0)
      {
        if (y <= yMax && y >= yMin)
        {
          System.out.println("INTERIOR");
        }
        else
        {
          System.out.println("EXTERIOR");
        }
      }
      else
      {
        if (y >= yMax && y <= yMin)
        {
          System.out.println("INTERIOR");
        }
        else
        {
          System.out.println("EXTERIOR");
        }
      }
      x = entrada.nextDouble();
      y = entrada.nextDouble();
    }
  }
}
