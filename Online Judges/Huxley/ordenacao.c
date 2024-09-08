int bubble()
{
  for (ordem = 9; ordem >= 1; ordem --)
  {
    for (bubble = 0; bubble < ordem; bubble ++)
    {
      if (altura[bubble] > altura[bubble + 1])
      {
        aux = altura[bubble];
        altura[bubble] = altura[bubble + 1];
        altura[bubble + 1] = aux;
      }
    }
  }
}

int orga()
{
  for (ordem = 0; ordem < 10; ordem ++)
  {
    for (bubble = 0; bubble < 10; bubble ++)
    {
      if (altura[ordem] < altura[bubble])
      {
        aux = altura[bubble];
        altura[bubble] = altura[ordem];
        altura[ordem] = aux;
      }
    }
  }
}
