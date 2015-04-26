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
  int sender_process_rank = 0;
  int process_tag = 1;
  int target_process_rank = 2;
  MPI_Request receive_request;
  MPI_Request send_request;
  MPI_Status status;
  char received_message[80];
  char processed_message[80];


  //INICIA O MPI
  MPI_Init(&argc, &argv);
  printf("\n ProcessCards::Init Iniciando processo de processamento de cartoes \n");

  //DETERMINA O RANK (identificador) DO PROCESSO
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  //DETERMINA O NUMERO TOTAL DE PROCESSOS DO PROGRAMA
  MPI_Comm_size(MPI_COMM_WORLD, &process_size);


  printf("\n ProcessCards::Rank :%d \n",process_rank);

  // Insere Barreira para Sincronizar os Processos
  // Essa barreira é importante estar antes do MPI_Recv pois precisamos ter uma
  // Mensagem enviada pelo outro programa que envia essa mensagem  logo esse processo
  // Precisa de uma barreira antes de Tentar Receber uma Mensagem.
  // Isso garante que quando o processo for ler uma mensagem essa mensagem já
  // Tenha sido enviada pelo programa que envia a mesangem lida do cartao.
  printf("\n ProcessCards::Barrier Barreira Ativa, Sincronizando Processos... \n");
  MPI_Barrier(MPI_COMM_WORLD);

  // Recebe Mensagem do Processo 0 que envia o card lido
  MPI_Recv(received_message, sizeof(received_message), MPI_BYTE,
             sender_process_rank, process_tag, MPI_COMM_WORLD, &status);
  printf("\n ProcessCards::Receive Recebendo Mensagem do Processo %d... \n",sender_process_rank);
  printf("\n ProcessCards::Receive Mensagem recebida: \n\n %s\n\n",received_message);


  // TO DO: Processamento dos dados recebidos e enviar mensagem processada
  strcpy(processed_message, received_message); // TO DO PROCESSAR A MENSAGEM
  // Envia a mensagem recebida ja processada para ser escrita no arquivo final

  printf("\n ProcessCards::Bsend Enviando Mensagem processada ao Processo %d... \n\n",target_process_rank);
  MPI_Bsend(processed_message, strlen(received_message), MPI_BYTE,
            target_process_rank,process_tag, MPI_COMM_WORLD);
  printf("\n ReadingCards::Bsend Mensagem enviada: \n\n %s\n\n",processed_message);

  MPI_Finalize();
}
