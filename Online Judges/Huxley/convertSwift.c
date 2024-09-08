#include <stdio.h>
#include <string.h>

int main()
{
  char nome[1000], numero[1000], end; long double longitude, latitude;
  while (scanf("Titulo : %[^\n]", nome) && scanf("\nSubtítulo :%[^\n]", numero) && scanf("\nLatitude : %Lf", &latitude) && (scanf("\nLongitude : %Lf", &longitude) || getchar()) && scanf("%c", &end) && end != 'E')
  {
    getchar(); getchar();
    nome[strlen(nome) - 1] = '\0';
    numero[strlen(numero) - 1] = '\0';

    printf("Lugar(nome: %c%s%c, número: %c%s%c, coordenada: CLLocationCoordinate2D(latitude: %.6Lf, longitude: %.6Lf), tipo: %calimentacao%c),\n\n", '"', nome, '"', '"', numero, '"', latitude, longitude, '"', '"');
  }
  return(0);
}

//Lugar(nome: "8º Juizado Especial Cível e Criminal da Capital", número: "Fórum Universitário", coordenada: CLLocationCoordinate2D(latitude: -9.558034, longitude: -35.780364), tipo: "bloco"),
