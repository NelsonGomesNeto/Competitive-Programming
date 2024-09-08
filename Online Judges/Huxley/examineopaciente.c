#include <stdio.h>

int main()
{
	float temperatura; scanf("%f\n", &temperatura);
	char tosse; 			 scanf("%c", &tosse);

	if (tosse == 'S')
	{
		if (temperatura >= 37)
			printf("Exames Especiais\n");
		else
			printf("Exames Basicos\n");
	}
	else if (tosse == 'N')
	{
		if (temperatura >= 37)
			printf("Liberado\n");
		else
			printf("Liberado\n");
	}
	else
		printf("Erro\n");

  return(0);
}
