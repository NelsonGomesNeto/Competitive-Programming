#include <stdio.h>
#include <math.h>

float maquina(float n){
  int arredondado, inteiro;
  float decimal;
  inteiro = n * 10;
  decimal = (n * 10) - inteiro;
  arredondado = round(decimal*100);
  if(decimal==0.0 || arredondado%10==0){
    return printf("%.1f ", n);
  }else{
    return printf("%.2f ", n);
  }
}
int main(){
  char qual;
  float temperatura, f, k, c;
  scanf("%c", &qual);
  scanf("%f", &temperatura);

  if(qual =='C'){
    if(temperatura<-273.0){
      printf("Valor de temperatura abaixo do minimo\n");
    }else{
      // c pra f
      f = (1.8*temperatura) + 32;
      maquina(f);
      printf("F\n");
      // c pra k
      k =  temperatura + 273;
      maquina(k);
      printf("K\n");

    }
  }else if(qual =='F'){
    if(temperatura<-459.67){
      printf("Valor de temperatura abaixo do minimo\n");
    }else{
      // f pra c
      c =  (temperatura - 32)/(1.8);
      maquina(c);
      printf("C\n");
      // f pra k
      k = (temperatura + 459.67)*(5/9);
      maquina(k);
      printf("K\n");
    }
  }else if(qual =='K'){
    if(temperatura<0.0){
      printf("Valor de temperatura abaixo do minimo\n");
    }else{
      // k pra c
      c = temperatura -273;
      maquina(c);
      printf("C\n");
      //k pra f
      f = (temperatura - 273) * 1.8 + 32;
      maquina(f);
      printf("F\n");
    }
  }
  return 0;
}
