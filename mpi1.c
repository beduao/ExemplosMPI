#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

int main(void) {
   int        comm_sz;               /* Número de processos    */
   int        my_rank;               /* Rank   do processo     */
   int        a = 2;
   int        b = 3;
   int soma = 0;

   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Obter rank (id) do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 


   printf("Número de processos: %d Rank do processos corrente: %d \n", comm_sz, my_rank);

   if(my_rank==0){
      int r=a+b;
      printf("%d\n",r);
      soma += r;
      for (int q=1; q<4; q++){
         MPI_Recv(&r, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         soma+=r;
      }
   printf("%d\n", soma);

   }else if(my_rank==1){
      int r=b-a;
      printf("%d\n",r);
      MPI_Send(&r, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   }else if(my_rank==2){
      int r=a*b;
      printf("%d\n",r);
      MPI_Send(&r, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   }else {
      int r=a-b;
      printf("%d\n",r);
      MPI_Send(&r, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   }



   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
