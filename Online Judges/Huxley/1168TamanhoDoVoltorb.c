#define N 5
sem_t garfo[5]; // 5 semáforos iniciados em 1
sem_t saleiro; // saleiro iniciado em 1

void filosofo (int i)
{
  while (1)
  {
    medita();
    sem_down(saleiro);
    sem_down(garfo [i]) ;
    sem_down(garfo [(i+1) % N]) ;
    come();
    sem_up(garfo [i]) ;
    sem_up(garfo [(i+1) % N]) ;
    sem_up(saleiro);
  }
}
