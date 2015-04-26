#include <stdio.h>
#include <mpi.h>

#define NUMERO_TAREFAS 100
#define TAG_INDICE 98
#define TAG_RES  99
#define ACABOU -1

/* Tarefa sequencial basica */
double calculo(int index) {
   return( index ) ;
}

void mestre() {
   double res_total = 0;
   double res_parcial;
   int p_id, p, i;
   int dest = 1;
   int task = 1;  /* indice da ultima tarefa que tenha sido mandada */
   int feito = 0; /* Número de tarefas processadas */
   MPI_Status status;

   MPI_Comm_size(MPI_COMM_WORLD, &p);
   for (dest=1 ; dest<p ; dest++) {
       MPI_Send(&task, 1, MPI_INT, dest, TAG_INDICE, MPI_COMM_WORLD);
       task++;
   }
   while(task < NUMERO_TAREFAS) {
     MPI_Recv(&res_parcial, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
    TAG_RES, MPI_COMM_WORLD, &status);
     res_total += res_parcial;
     dest = status.MPI_SOURCE; feito++;
     MPI_Send(&task, 1, MPI_INT, dest, TAG_INDICE, MPI_COMM_WORLD);
     task++;
   }
   /* Acabou. Ainda manda uma mensagem de encerramento a cada escravo. */
   task = ACABOU;
   for (dest=1 ; dest<p ; dest++)
       MPI_Send(&task, 1, MPI_INT, dest, TAG_INDICE, MPI_COMM_WORLD);
   /* E espera pelos últimos resultados a serem recebidos */
   while (feito < NUMERO_TAREFAS-1) {
     MPI_Recv(&res_parcial, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
    TAG_RES, MPI_COMM_WORLD, &status);
     res_total += res_parcial;
     feito++;
   }
   printf("Resultado: %lf.", res_total);
   if (res_total != (NUMERO_TAREFAS * (NUMERO_TAREFAS-1) / 2))
      printf("... ERRADO.\n");
   else
      printf("... CERTO.\n");
}

void escravo() {
  int i=0;
  MPI_Status status;
  double res_parcial;
  while (i != ACABOU) {
     MPI_Recv(&i, 1, MPI_INT, 0, TAG_INDICE, MPI_COMM_WORLD, &status);
     if (i != ACABOU) {
        res_parcial = calculo(i);
        MPI_Send(&res_parcial, 1, MPI_DOUBLE, 0, TAG_RES, MPI_COMM_WORLD);
     }
  }
}

int main(int argc, char* argv[]) {
   int p_id, p, i;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Comm_rank(MPI_COMM_WORLD, &p_id);
   if (p_id==0) /* 0 eh o mestre */
      mestre();
   else  /* os demais sao os escravos */
      escravo();
   MPI_Finalize();
   return(0);
}
