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
#include <stdlib.h>


void write_file(char *mesage);


int main(int argc, char **argv) {

  int process_rank;
  int process_size;
  int sender_process_rank = 1;
  int process_tag = 1;
  MPI_Request receive_parsed_text_request;
  MPI_Status status;
  char *message_processed_received;

  message_processed_received = (char*) malloc(sizeof(char)*80);


  //INICIA O MPI
  MPI_Init(&argc, &argv); /*START MPI */
  printf("\n WriteFile::Init Iniciando processo de escrita em arquivo \n");

  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  printf("\n WriteFile::Rank :%d \n",process_rank);

  MPI_Comm_size(MPI_COMM_WORLD, &process_size);

  printf("\n WriteFile::Barrier Barreira Ativa, Sincronizando Processos... \n");
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Recv(message_processed_received, 90,
           MPI_BYTE,sender_process_rank, process_tag, MPI_COMM_WORLD,
             &status);

  printf("\n WriteFile::Receive Recebendo Mensagem do Processo %d... \n\n",sender_process_rank);
  //TO DO criar funcao para escrever arquivo de saida
  printf("\n WriteFile::write Escrevendo Arquivo de Saida... \n\n");
  write_file(message_processed_received);

  printf("\n Arquivo de saida em : card_processed.txt \n");
  printf("\n ----- Fim de Execucao ----- \n\n");


  //SAIR DO MPI MPI
  MPI_Finalize();
}

void write_file(char *mesage){
  FILE *file;
  file = fopen("card_processed.txt","w+");
  fprintf(file,mesage);
  fclose(file);
}
