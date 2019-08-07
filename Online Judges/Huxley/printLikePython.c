void printBug(double n)
{
  if ((int) round(n * 100) % 10 == 0)
    printf("%.1lf\n", round(n * 10) / 10);
  else
    printf("%.2lf\n", round(n * 100) / 100);
}
