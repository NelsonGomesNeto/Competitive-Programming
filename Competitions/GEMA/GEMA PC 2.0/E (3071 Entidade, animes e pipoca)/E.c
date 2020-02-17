#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
     long int eps, i, j, perguntas, res, ep, pipoca;
    
    scanf("%ld", &eps);
    
    long int duracao[eps];
    
    for(i = 0; i < eps; i++)
    {
        scanf("%ld", &duracao[i]);
    }
    
    scanf("%ld", &perguntas);

    i = 0;
    
    while(i < perguntas)
    {
        scanf("%ld %ld", &ep, &pipoca);
        
        if(duracao[ep-1] <= pipoca)
        {
            for(j = ep-1; j < eps; j++)
            {
                pipoca = pipoca - duracao[j];
                
                if(pipoca < 0)
                {
                    break;
                }
                        
                res = j+1;
            }
        }
        else if(duracao[ep-1] > pipoca)
        {
            res = -1;
        }
        
        printf("%ld\n", res);
        
        i++;
    }
    
    
	return 0;
}