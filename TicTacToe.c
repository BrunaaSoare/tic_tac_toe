#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// variaveis globais
int i, j;
int vitoria = 0;
int ciclo = 0;
int player_x_points = 0;
int player_o_points = 0;
int top_player[2];
int troca_top_1;

char board[3][3];
char coordenada[9];
char jogador_x_nome[50];
char jogador_o_nome[50];
char jogador_atual;

 typedef struct {
  char players_top_10[50];
  }score;

score guardar_top_players[10];

void ranking() {
  FILE *pont_arq; // cria variável ponteiro para o arquivo
  pont_arq = fopen("ranking.txt", "w");
  // testando se o arquivo foi realmente criado
  if (pont_arq == NULL) {
    printf("Erro na abertura do arquivo!");
  }
  // usando fprintf para armazenar a string no arquivo
  fprintf(pont_arq, "%s\n%i\n", jogador_x_nome, player_x_points);
  fprintf(pont_arq, "%s\n%i\n", jogador_o_nome, player_o_points);
  fclose(pont_arq);
  // abertura para releitura e amostragem do rank
  pont_arq = fopen("ranking.txt", "r");
  // testando se o arquivo foi realmente criado
  if (pont_arq == NULL) {
    printf("Erro na abertura do arquivo!");
  }
  // fscanf para guardar os nomes do ranking,txt em variaveis.
  for(int i = 0; i < 2 ; i++){
    fscanf(pont_arq, "%s\n%d", guardar_top_players[i].players_top_10,&top_player[i]); // LEITURA
  }  
  int i=0,j=1;
  printf("\t\t\t------------RANKING------------\n\n");
  
  if(top_player[i]<top_player[j]){
    
    troca_top_1=top_player[i];
    top_player[i]=top_player[j];
    top_player[j]=troca_top_1;
    for(int i = 0; i < 2 ; i++){
      printf("\t\t\t\t %dº ---------- %s || %d\n",i+1,               
      guardar_top_players[j].players_top_10,top_player[i]);
      j--;
      
    }
    
  }else{
    for(int i = 0; i < 2 ; i++){
    printf("\t\t\t\t %dº ---------- %s || %d\n",i+1,               
    guardar_top_players[i].players_top_10,top_player[i]);
    }
  }
  fclose(pont_arq);
}

void limpar_tabuleiro() {
  for (int i = 0; i < 9; i++) {
    coordenada[i] = ' ';
  }
}

void posicao() {

  int coordenada[9];
  int indice = 0;

  for (int i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      coordenada[indice] = board[i][j];
      indice++;
    }
  }
}

void jogador_vencedor() {
  if (jogador_atual == 'X') {
    printf("\t\t\t\t\t Voce venceu! ");
    puts(jogador_x_nome);
    player_x_points += 3;
    player_o_points -= 1;
  } else {
    printf("\t\t\t\t\t Voce venceu! ");
    puts(jogador_o_nome);
    player_o_points += 3;
    player_x_points -= 1;
  }
}

void verificar_vertical() {

  if (coordenada[0] == jogador_atual && coordenada[3] == jogador_atual &&
          coordenada[6] == jogador_atual ||
      coordenada[1] == jogador_atual && coordenada[4] == jogador_atual &&
          coordenada[7] == jogador_atual ||
      coordenada[2] == jogador_atual && coordenada[5] == jogador_atual &&
          coordenada[8] == jogador_atual) {
    jogador_vencedor();
    vitoria = 1;
  }
}

void verificar_diagonal() {
  if (coordenada[0] == jogador_atual && coordenada[4] == jogador_atual &&
      coordenada[8] == jogador_atual) {
    jogador_vencedor();
    vitoria = 1;
  }

  if (coordenada[2] == jogador_atual && coordenada[4] == jogador_atual &&
      coordenada[6] == jogador_atual) {
    jogador_vencedor();
    vitoria = 1;
  }
}

void verificar_horizontal() {
  if (coordenada[0] == jogador_atual && coordenada[1] == jogador_atual &&
          coordenada[2] == jogador_atual ||
      coordenada[3] == jogador_atual && coordenada[4] == jogador_atual &&
          coordenada[5] == jogador_atual ||
      coordenada[6] == jogador_atual && coordenada[7] == jogador_atual &&
          coordenada[8] == jogador_atual) {
    jogador_vencedor();
    vitoria = 1;
  }
}

void check_victory() {
  verificar_diagonal();
  verificar_horizontal();
  verificar_vertical();
}

void jogo_da_velha() {
  
  int i;
  int alterar_usuario = 0; // alternar os usuarios
  //system(“cls”);
  do {

    if (alterar_usuario % 2 == 0) {
      printf("\n\t\t\t\t X || Player : ");
      puts(jogador_x_nome);
    } else {
      printf("\n\t\t\t\t O || Player : ");
      puts(jogador_o_nome);
    }

    printf("\t\t\tDigite a posicao desejada : ");
    scanf("%d", &i);
    getchar();
    
    posicao(); // 1 posicao
    
    int stack = 0;
    
    while (i <= 0 || i > 9) {
      printf("\n\t\t\t\tEssa posicao nao existe!\n\t\t\tPor favor digite uma "
             "posicao valida:");
      scanf("%d", &i);
      getchar();

      stack++;

      if (stack == 2) {
        printf("\n\t\t\t\t\t\tAlerta!!!!\n\t\t\tProximo erro ocorrera a "
               "descontinuacao do\n\t\t\tprograma e todo progresso será "
               "perdido!\n\n");
        printf("\t\t\tDigite uma posicao valida! ");
        scanf("%d", &i);
        getchar();

        if (i <= 0 || i > 9 && stack == 3) {
          exit(0);
        }
      }
    }

    while (coordenada[i - 1] == 'X' || coordenada[i - 1] == 'O') {

      printf("\n\t\t\tA casa ja está ocupada!\n\t\t\tDigite uma posicao nao "
             "ocupada! ");
      scanf("%d", &i);
      getchar();

      stack++;

      if (stack == 2) {
        printf("\n\t\t\t\t\t\tAlerta!!!!\n\t\t\tProximo erro ocorrera a "
               "descontinuacao do\n\t\t\tprograma e todo progresso será "
               "perdido!\n\n");
        printf("\t\t\tDigite uma posicao nao ocupada! ");
        scanf("%d", &i);
        getchar();
        
        if (coordenada[i - 1] == 'X' ||
            coordenada[i - 1] == 'O' && stack == 3) {
          exit(0);
        }
      }
    }
    if (alterar_usuario % 2 == 0) {
      coordenada[i - 1] = 'X';
      jogador_atual = 'X';
    } else {
      coordenada[i - 1] = 'O';
      jogador_atual = 'O';
    }
    alterar_usuario++;

    int contador = 0;
    printf("\n\n\t\t\t\t");

    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 3; i++) {
        printf("|\t%c\t|", coordenada[contador]);
        contador++;
      }
      printf("\n\t\t\t\t");
    }
    printf("\n\n");
    
    check_victory();
    ciclo++; 
  } while (vitoria == 0 && ciclo < 9);
  if(ciclo == 9 && vitoria == 0){
    printf("\t\t\t\tDeu Velha!! Ninguem pontuou!\n\n");
  }
}

void imprimir() {
  printf("\n\t\t\t\t|| Jogo Da Velha ||\n\nObs : Digite onde deseja posicionar "
         "o [x] ou [o]\nconforme o exemplo a seguir."
         "\n\n\t\t\t "
         "\t1\t|\t2\t|\t3\n\t\t\t \t4\t|\t5\t|\t6\n\t\t\t "
         "\t7\t|\t8\t|\t9\n\n\n");
}

int main(void) {
  char opcao_jogar_dnv;
  
  imprimir();
  
  printf("Digite o nome do usuario que será o X : ");
  fgets(jogador_x_nome, 30, stdin);

  printf("\nDigite o nome do usuario que será o O : ");
  fgets(jogador_o_nome, 30, stdin);
  //system("cls");
  do {
    vitoria = 0;
    ciclo = 0;
    limpar_tabuleiro();
    posicao();
    jogo_da_velha();
    ranking();
    printf("\n\t\t\t\t deseja jogar novamente?\n\t\t\t\t s - Sim\n\t\t\t\t n - Nao\n");
    scanf("%c", &opcao_jogar_dnv);
    getchar();
  } while (opcao_jogar_dnv == 's' || opcao_jogar_dnv == 'S');

  printf("\nObrigado por ter jogado nosso jogo!!");
  printf("\n\n\t\t\t\t\tCreditos\n\n\t\t\t\tBruna Gabriela\n\t\t\t\tGabriel "
         "Fernandes\n\t\t\t\tPablo Rocha ");
  return 0;
}
