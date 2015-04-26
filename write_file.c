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

  int process_rank;
  int process_size;
  int sender_process_rank = 1;
  int process_tag = 1;
  MPI_Request receive_parsed_text_request;
  MPI_Status status;
  char message_processed_received[80];

  //INICIA O MPI
  MPI_Init(&argc, &argv); /*START MPI */
  printf("\n WriteFile::Init Iniciando processo de escrita em arquivo \n");

  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  printf("\n WriteFile::Rank :%d \n",process_rank);

  MPI_Comm_size(MPI_COMM_WORLD, &process_size);

  printf("\n WriteFile::Barrier Barreira Ativa, Sincronizando Processos... \n");
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Recv(message_processed_received, sizeof(message_processed_received),
           MPI_BYTE,sender_process_rank, process_tag, MPI_COMM_WORLD,
             &status);

  printf("\n WriteFile::Receive Recebendo Mensagem do Processo %d... \n\n",sender_process_rank);

//  puts("Write receveu O :");

  //Removendo lixo na ultima posição que chega ao message_processed_received
  message_processed_received[(strlen(message_processed_received)-1)] = '\0';
//  puts(message_processed_received);

  printf("\n WriteFile::write Escrevendo Arquivo de Saida... \n\n");
  //TO DO : Escrever string recebida no arquivo
  printf("\n Arquivo de saida em :  \n");
  printf("\n ----- Fim de Execucao ----- \n\n");


  //SAIR DO MPI MPI
  MPI_Finalize();
}
