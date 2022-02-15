#define _GNU_SOURCE


#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

    double *tabA;
    double *tabC;
    double *tabB;


void * add(void * data)
{
    size_t index;
    size_t iter;

    /*=>Recuperation de l'index, c'est a dire index = ... */
    index = ((size_t)data);
    printf("l'index est : %d \n", index);
    tabC[index] = tabA[index] + tabB[index];
    printf("%lf \n", tabC[index]);
    printf("hello \n");
    return(data);
}


int main(int argc,char ** argv){

    int nblignes = 10;
    int nbThread = atoi(argv[2]);
    pthread_t *addTh;
    pthread_t *multTh;
    size_t *addData;
    void     * threadReturnValue;

    if(argc < 3){
        printf("Nombre d'argument < 3\n");
        exit(EXIT_FAILURE);
    }

   

    tabA = (double *)malloc(nblignes*sizeof(double));
    tabB = (double *)malloc(nblignes*sizeof(double));
    tabC = (double *)malloc(nblignes*sizeof(double));

 
 for(int i = 0; i < nblignes; i++){
        tabA[i] = i+1;
        tabB[i] = i+1;
    }

    /* Allocation dynamique du tableau pour les threads d'addition */

    addTh=(pthread_t )malloc(nbThread*sizeof(pthread_t));

    /* Allocation dynamique du tableau des MulData */

    addData=(size_t )malloc(nbThread*sizeof(size_t));

    /*=>Creer les threads d'addition */

    for(int i = 0; i < nbThread ; i++)
    {
    if(pthread_create(&addTh[i],(pthread_attr_t *)0,add,NULL))
        {
        fprintf(stderr,"Pb add creation !\n");
        return(EXIT_FAILURE);
        }
       // printf("%f, %f, %f\n",tabA[i], tabB[i], tabC[i]);
    }

for(int i=0;i<nbThread;i++)
  {
  if(pthread_join(addTh[i],&threadReturnValue)) 
    {
    fprintf(stderr,"Pb add join !\n");
    return(EXIT_FAILURE);
    }
  }

  



    free(tabA);
    free(tabB);
    free(tabC);



}