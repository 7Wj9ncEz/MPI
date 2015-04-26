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
  int target_process_rank = 1;
  int process_tag = 1;
  MPI_Request request;

  //INICIA O MPI
  MPI_Init(&argc, &argv); /*START MPI */
  printf("\n ReadingCards::Init Iniciando processo de leitura de cartoes \n");

  //DETERMINA O RANK DO PROCESSO
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  printf("\n ReadingCards::Rank :%d \n",process_rank);

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

  //TO DO criar uma função separada para leitura de cartões

  //LER AS LINHAS DO CARTÃO
  while( fscanf(file_card,"%s",card_content) != EOF ){
    //COPIAR STRING LIDA PARA CONTEUDO DA MENSAGEM
    sprintf(message_content, "%s", card_content);

    //ENVIAR MENSAGEM COM AS LINHAS PARA OUTRO PROCESSO
  }

  // Fim de leitura de arquivo
  fclose(file_card);

  //Enviar mensagem em modo Bufferizardo MPI_Bsend

  printf("\n ReadingCards::Bsend Enviando Mensagem ao Processo de Rank = %d... \n",target_process_rank);

  //Neste modo MPI_Bsend o usuário garante a bufferização, pelo sistema, das
  //mensagens enviadas.Este modo um overhead de sistema adicional é ocasionado
  //pela cópia dos dados do buffer da mensagem para o buffer do usuário.
  //Overhead de sincronismo é eliminado na tarefa emissora, para ela é irrelevante o
  //momento em que a tarefa receptora executa a operação de recebimento.
  //Algum overhead de sincronismo pode acontecer na tarefa receptora, ela
  //precisa esperar a mensagem chegar.
  MPI_Bsend(message_content, strlen(message_content), MPI_BYTE,
             target_process_rank,process_tag, MPI_COMM_WORLD);

  printf("\n ReadingCards::Bsend Mensagem enviada: \n\n %s\n\n",message_content);

  //Barreira para sincronização dos processos
  //Essa  barreira é importante ficar depois do MPI_Bsend para garantir que os
  //outros processos só irão a mensagem depois de enviada.
  //Nos outros processos a Barreira deve ser adicionada antes do MPI_Recv
  //Para que assim só sejam liberados depois do envio da mensagem.
  printf("\n ReadingCards::Barrier Barreira Ativa, Sincronizando Processos... \n");
  MPI_Barrier(MPI_COMM_WORLD);

  //SAIR DO MPI MPI
  MPI_Finalize();
}
