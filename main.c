#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro {
  int id;
  char titlo[50];
  char autor[50];
  char descricao[200];
  char data_pub[10];

} livros;

void menu();

void pesquisar();
void listar();
void inserir();
void eliminar();
void atualizar();

int main() {
  setlocale(LC_ALL, "");
  menu();
  return 0;
}

void menu() {
  char op = 0;
  int is_valid = 1;

  do {
    printf("\n[1] - Pesquisar livros \n");
    printf("[2] - Listar livros \n");
    printf("[3] - Inserir livros \n");
    printf("[4] - Atualizar livro \n");
    printf("[5] - Eliminar livros \n");
    printf("[0] - Sair \n\n");

    printf("Selecione uma opção: \n");
    scanf("%c", &op);

    switch (op) {
    case '1':
      // is_valid = 1;
      // pesquisar();
      break;
    case '2':
      // listar();
      break;
    case '3':
      inserir();
      break;
    case '4':
      // atualizar();
      break;
    case '5':
      //  eliminar();
      break;
    case '0':
      printf("\nA sair... \n");
      exit(1);
      break;

    default:
      printf("\nOpção inválida!\n");
      is_valid = 0;

      // limpa o buffer
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      break;
    }

  } while (!is_valid);
}

void inserir() {
  char c;

  printf("Introduza id do livro: ");

  // Mais seguro que scanf
  fscanf(stdin, "%i", &livros.id);

  // Come o '\n' deixado pelo fscanf acima
  // Caso contrário é lido no 'fgets' abaixo e não o executa
  scanf("%c", &c);

  printf("Introduza o titulo do livro: ");
  fgets(livros.titlo, 50, stdin);

  printf("Introduza o nome do autor: ");
  fgets(livros.autor, 50, stdin);

  printf("Introduza uma descrição do livro: ");
  fgets(livros.descricao, 200, stdin);

  printf("Introduza a data de publicação: ");
  fgets(livros.data_pub, 10, stdin);
}
