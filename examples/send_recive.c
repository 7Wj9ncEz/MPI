#include <mpi.h>   /* PROVIDES THE BASIC MPI DEFINITION AND TYPES */
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {

  int my_rank;
  int source;
  int size, i,t;
  char greeting[100];
  MPI_Status stat;

  MPI_Init(&argc, &argv); /*START MPI */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /*DETERMINE RANK OF THIS PROCESSOR*/
  MPI_Comm_size(MPI_COMM_WORLD, &size); /*DETERMINE TOTAL NUMBER OF PROCESSORS*/

  /*
     MPI_Recv(1,2,3,4,5,6,7)
     1: void* endereco inicial do buffer de recepção
     2: count numero maximo de dados a serem recebidos
     3: MPI_DATA_TYPE tipo do dado
     4: source rank do processo remetente, quem me enviou?
     5: tag ????
     6: comunicador
     7: status status da acao MPI_SOURCE_TAG, MPI_TAG, MPI_ERROR.
     MPI_Send(1,2,3,4,5,6)
     1: void* message endereço inicial do dado a ser enviado
     2: count numero de dados
     3: MPI_TYPE tipo do dado
     4: dest rank do processo destino, pra quem vou enviar?
     5: tag ????
     6: comunicador

     count e data_type permitem o sistema identificar o final da mensagem
     eles tem uma sequencia de valores da contagem, cada um contendo um tipo
     de dado MPI
     Existe um source coringa chamado MPI_ANY_SOURCE, pra destino n existe.
     Existe uma tag coringa MPI_ANY_TAG

     Tag serve para distiguir mensagens de um unico processo, inteiro designado
     a mensagem costuma ser um int, "classifica as mensagens"
     Comunicador é coleção de processos que podem enviar uns processos p outros

  */

  if (my_rank ==0) {

    sprintf(greeting, "Processo %d ZUEIRAAAAA HAHAHAAH", my_rank);
    for (source = 1; source < size; source++){
      MPI_Recv(greeting, sizeof(greeting), MPI_BYTE, source, 1, MPI_COMM_WORLD, &stat);
      puts(greeting);
    }
  }
  else {
    puts("Preenchendo buffer de mensagem");
    sprintf(greeting, "Processo %d Enviando mensagem ao processo 0 \n", my_rank);
    MPI_Send(greeting, strlen(greeting)+1, MPI_BYTE, 0,1,MPI_COMM_WORLD);
  }

  if (my_rank == 0) printf("Entrei no zero");
  MPI_Finalize();  /* EXIT MPI */

}
