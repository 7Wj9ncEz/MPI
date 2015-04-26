#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <string.h>
int main(int argc, char* argv[]) {


   int rank, tam, tag=99;
   char msg[20];
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &tam);

   if (rank == 0) {
     strcpy( msg, "Ola Mundo!\n");
     MPI_Send( msg, strlen(msg)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
   // Envia uma mensagem para processo “1”
   }
   else {
     strcpy( msg, "Olá turma!\n");
     MPI_Recv( msg, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
     // Recebe uma mensagem provinda do processo “0”
     printf(msg);
  }
 MPI_Finalize();
 return 0;
}
