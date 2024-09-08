for (int digit = 0; digit <= 9; digit++)
{
  int count = 0;
  int x = n;
  while (x > 0)
  {
    int a = x % 10;
    if (a == digit)
      count++;
    x /= 10;
  }
}