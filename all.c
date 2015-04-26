//  MPI_Recv(1,2,3,4,5,6,7)
//  1: void* endereco inicial do buffer de recepção
//  2: count numero maximo de dados a serem recebidos
//  3: MPI_DATA_TYPE tipo do dado
//  4: source rank do processo remetente, quem me enviou?
//  5: tag distiguir mensagens de um unico process
//  6: comunicador
//  7: status status da acao MPI_SOURCE_TAG, MPI_TAG, MPI_ERROR.
//  MPI_Send(1,2,3,4,5,6)
//  1: void* message endereço inicial do dado a ser enviado
//  2: count numero de dados
//  3: MPI_TYPE tipo do dado
//  4: dest rank do processo destino, pra quem vou enviar?
//  5: tagdistiguir mensagens de um unico process
//  6: comunicador

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {


  int target_process_rank = 1;
  int process_tag = 1;
  int process_rank;
  int process_size;
  int process_tag = 1;

  //INICIA O MPI
  MPI_Init(&argc, &argv); /*START MPI */

  //DETERMINA O RANK DO PROCESSO
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  //DETERMINA O NUMERO TOTAL DE PROCESSOS DO PROGRAMA
  MPI_Comm_size(MPI_COMM_WORLD, &process_size);

  //CRIA STRING PARA LEITURA DO CARTÃO
  char card_content[80];

  //CRIA STRING PARA MENSAGEM
  char message_content[80];

  // CRIA PONTEIRO PARA ARQUIVO
  FILE *file_card;

  //TO DO: PEGAR ARQUIVO DO ARGV
  file_card = fopen("card_1.txt","r");

  //LER AS LINHAS DO CARTÃO
  while( fscanf(file_card,"%s",card_content) != EOF ){
    //COPIAR STRING LIDA PARA CONTEUDO DA MENSAGEM
    sprintf(message_content, "%s", card_content);

    //ENVIAR MENSAGEM COM AS LINHAS PARA OUTRO PROCESSO
  }

  fclose(file_card);

  printf("\n Estou no reading cards e o rank e proceeso e :%d \n",process_rank);
  if (process_rank == 0) {

    puts(message_content);
    MPI_Send(message_content, strlen(message_content)+1, MPI_BYTE,
             target_process_rank,process_tag, MPI_COMM_WORLD);
  }

  if (process_rank == 1) {

    MPI_Recv(received_message, sizeof(received_message), MPI_BYTE,
             sender_process_rank, process_tag, MPI_COMM_WORLD, &receive_status);
    puts("RECEBI O :");
    puts(received_message);

  }



  //SAIR DO MPI MPI
  MPI_Finalize();
}
