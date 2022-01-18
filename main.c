#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// numeros de valores d
#define LIVRO_ARR_LEN 5

struct Livro {
  int id;
  char titlo[50];
  char autor[50];
  char descricao[200];
  char data_pub[10];

} livro;

int numLivros = 2;

struct Livro livros[LIVRO_ARR_LEN];

// A funcionar
void menu();

// A ser feito (Cebola)
void pesquisar();

// A funcionar
void listar();

// A funciominar (Cebola)
void inserir();
void eliminar();
void atualizar();

int main() {
  setlocale(LC_ALL, "");

  livros[0].id = 0;
  strcpy(livros[0].titlo, "O youtuber");
  strcpy(livros[0].autor, "Evando Vieira");
  strcpy(livros[0].descricao, "alguma descrição");
  strcpy(livros[0].data_pub, "20/22");

  livros[1].id = 1;
  strcpy(livros[1].titlo, "O gamer");
  strcpy(livros[1].autor, "Cebola");
  strcpy(livros[1].descricao, "alguma descrição");
  strcpy(livros[1].data_pub, "20/22");
  menu();

  return 0;
}

void menu() {

  do {
    char op = 0;

    printf("\n[1] - Pesquisar livros \n");
    printf("[2] - Listar livros \n");
    printf("[3] - Inserir livros \n");
    printf("[4] - Atualizar livro \n");
    printf("[5] - Eliminar livros \n");
    printf("[6] - Sair \n\n");

    printf("Selecione uma opção: \n");
    scanf("%i", &op);

    switch (op) {
    case 1:
      pesquisar();
      break;
    case 2:
      listar();
      break;
    case 3:
      inserir();
      break;
    case 4:
      // atualizar();
      break;
    case 5:
      eliminar();
      break;
    case 6:
      printf("\nA sair... \n");
      exit(1);

    default:
      printf("\nOpção inválida!\n");

      // limpa o buffer
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      break;
    }

  } while (1);
}

void pesquisar() {
  int i;
  int idNum;
  int check = 0;

  printf("\nIntroduza id do livro: ");
  scanf("%d", &idNum);

  for (i = 0; i < numLivros; i++) {
    if (idNum == livros[i].id) {
      check = 1;
      break;
    }
  }

  if (check) {
    printf("\nTítulo: %s", livros[idNum].titlo);
    printf("\nAutor: %s", livros[idNum].autor);
    printf("\nDescrição: %s", livros[idNum].descricao);
    printf("\nData de publicação: %s\n", livros[idNum].data_pub);
  } else
    printf("\nErro: O id não existe\n");

  menu();
}

void inserir() {
  char c;

  printf("Introduza id do livro: ");

  // Mais seguro que scanf
  fscanf(stdin, "%i", &livros[numLivros + 1].id);

  // Come o '\n' deixado pelo fscanf acima
  // Caso contrário é lido no 'fgets' abaixo e não o executa
  scanf("%c", &c);

  printf("Introduza o titulo do livro: ");
  fgets(livros[numLivros + 1].titlo, 50, stdin);

  printf("Introduza o nome do autor: ");
  fgets(livros[numLivros + 1].autor, 50, stdin);

  printf("Introduza uma descrição do livro: ");
  fgets(livros[numLivros + 1].descricao, 200, stdin);

  printf("Introduza a data de publicação: ");
  fgets(livros[numLivros + 1].data_pub, 10, stdin);

  numLivros++;

  // menu();
}

void listar() {
  int i;
  printf("Lista de todos os livros:\n\n");
  for (i = 0; i <= numLivros; i++) {
    printf("%d --- %s\n", livros[i].id, livros[i].titlo);
    printf("       %s\n", livros[i].autor);
    printf("       %s\n", livros[i].descricao);
    printf("       %s\n", livros[i].data_pub);
    printf("\n");
  }
  // menu();
}

void eliminar() {
  int i;
  int idNum;
  int check;
  int warn;

  for (i = 0; i < numLivros; i++) {
    printf("\nId: %d", livros[i].id);
    printf("\nTítulo: %s\n", livros[i].titlo);
  }

  // printf("Introduza");
  printf("\n");
  // menu();
}

void atualizar() {
  int i;
  printf("Qual é o livro que quer atualizar?\n");
  scanf("%d", &i);
}
