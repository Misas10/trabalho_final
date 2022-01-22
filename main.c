#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

// nome do ficheiro
const char *NOME_FIC = "livros.bin";

// pointer do ficheiro
FILE *file;

typedef struct Livro Livro;
int numLivros = 2;

struct Livro {
  int id;
  char titlo[50];
  char autor[50];
  char descricao[200];
  char data_pub[10];
} livro;

// FEITO 😄
void menu();

// FEITO 😄
int pesquisar();

// FEITO 😄
int listar();

// FEITO 😄
int inserir();

// FEITO 😄
int eliminar();

// FEITO 😄
int atualizar();

void mostrarLivro(struct Livro str_livro);
int validar_id(char *str);

int main() {
  setlocale(LC_ALL, "");

  if ((file = fopen(NOME_FIC, "ab+")) == NULL) {
    puts("Não foi possível abrir o ficheiro \n");
  }

  fclose(file);
  menu();

  return 0;
}

void menu() {

  do {
    int op = 0;

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
      atualizar();
      break;

    case 5:
      eliminar();
      break;

    case 6:
      printf("\nA sair... \n");
      exit(2);

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

int pesquisar() {
  int idNum;
  int check = 0;

  file = fopen(NOME_FIC, "rb");
  if (file == NULL) {
    puts("Erro ao ler o ficheiro");
    return 1;
  }

  printf("\nIntroduza id do livro: ");
  scanf("%d", &idNum);

  while (fread(&livro, sizeof(Livro), 1, file)) {
    if (idNum == livro.id) {
      check = 1;
      break;
    }
  }
  printf("\n");

  if (check)
    mostrarLivro(livro);
  else
    printf("ERRO: O id não existe\n");

  fclose(file);
  return 0;
}

int inserir() {

  file = fopen(NOME_FIC, "ab+");
  char c;
  int id;

  if (file == NULL) {
    puts("ERRO: Não foi possível abrir o ficheiro\n");
    return 0;
  }

  // Mais seguro que scanf
  id = validar_id("Introduza id do livro: ");

  while (fread(&livro, sizeof(Livro), 1, file))
    if (livro.id == id) {
      puts("ERRO: Este id já existe. \n\n");
      return 1;
    }

  livro.id = id;

  printf("Introduza o titulo do livro: ");
  fgets(livro.titlo, 50, stdin);

  printf("Introduza o nome do autor: ");
  fgets(livro.autor, 50, stdin);

  printf("Introduza uma descrição do livro: ");
  fgets(livro.descricao, 200, stdin);

  printf("Introduza a data de publicação: ");
  fgets(livro.data_pub, 10, stdin);

  // Esccreve no ficheiro
  fwrite(&livro, sizeof(Livro), 1, file);
  fclose(file);

  return 0;
}

int listar() {

  if ((file = fopen(NOME_FIC, "rb")) == NULL) {
    puts("ERRO: Não é possível ler o ficheiro\n");
    return 1;
  }

  // recebe o número de elementos no ficheiro
  int elemens_read = fread(&livro, sizeof(Livro), 1, file);

  // Caso não existam elemtos guardados no ficheiro
  if (elemens_read == 0) {
    printf("\nNão Existem livros aguardados!\n");
    fclose(file);
    return 2;
  }
  fclose(file);

  if ((file = fopen(NOME_FIC, "rb")) == NULL) {
    puts("ERRO: Não é possível ler o ficheiro\n");
    return 1;
  }

  printf("\nLista de todos os livros:\n\n");

  while (fread(&livro, sizeof(Livro), 1, file)) {
    mostrarLivro(livro);
  }

  fclose(file);
  return 0;
}

int eliminar() {
  FILE *file_temp;
  int id;
  int found = 0;
  char choice, c;

  if ((file = fopen(NOME_FIC, "rb")) == NULL) {
    puts("\nErro: Não foi possível ler o ficheiro\n");
    return 1;
  }

  // Cria um ficheiro temporário
  if ((file_temp = fopen("temp.bin", "wb")) == NULL) {
    puts("\nERRO: Não foi possível abrir o ficheiro\n");
    return 1;
  }

  id = validar_id("\nIntroduza um id válido do livro que deseja eliminar: ");

  while (fread(&livro, sizeof(Livro), 1, file)) {

    if (id == livro.id) {

      mostrarLivro(livro);

      printf("\nDeseja eliminar este livro? (S/n): ");
      // come o '\n'
      scanf("%c", &c);

      choice = getchar();

      if (choice == 'S' || choice == 's') {
        printf("\nRegisto eliminado com sucesso! \n");
        found = 1;
      } else
        found = 2;

    } else
      fwrite(&livro, sizeof(Livro), 1, file_temp);
  }

  if (!found) {
    printf("\nERRO: Não foi possível encontrar este id: %i\n", id);
  }

  if (found == 2) {
    printf("Id %i não foi eliminado\n", id);
    remove("temp.bin");
    return 2;
  }

  fclose(file);
  fclose(file_temp);

  remove(NOME_FIC);
  rename("temp.bin", NOME_FIC);

  return 0;
}

int atualizar() {
  int id;
  int existe = 0;
  char resp, c;

  file = fopen(NOME_FIC, "rb+");
  if (file == NULL) {
    printf("ERRO: Não foi possível ler o ficheiro\n");
    return 0;
  }

  printf("Qual é o id do livro que deseja atualizar?\n");
  scanf("%d", &id);

  while (fread(&livro, sizeof(Livro), 1, file)) {

    if (livro.id == id) {
      existe = 1;

      id = validar_id("Digite um novo id válido: ");

      printf("Introduza o novo titulo do livro: ");
      fgets(livro.titlo, 50, stdin);

      printf("Introduza o novo nome do autor: ");
      fgets(livro.autor, 50, stdin);

      printf("Introduza uma nova descrição do livro: ");
      fgets(livro.descricao, 200, stdin);

      printf("Introduza a nova data de publicação: ");
      fgets(livro.data_pub, 10, stdin);

      fseek(file, -sizeof(Livro), 1);

      // Esccreve no ficheiro
      fwrite(&livro, sizeof(Livro), 1, file);
      break;
    } else
      existe = 0;
  }

  if (existe)
    printf("\nLivro alterado com sucesso! \n");
  else
    printf("\nERRO: este id não existe\n");

  fclose(file);
}

void mostrarLivro(struct Livro str_livro) {
  printf("\n");
  printf("ID: %i \n", str_livro.id);
  printf("AUTOR: %s", str_livro.autor);
  printf("TÍTULO: %s", str_livro.titlo);
  printf("DESCRIÇÃO: %s", str_livro.descricao);
  printf("DATA DE PUBLICAÇÃO: %s", str_livro.data_pub);
  printf("\n#############################################");
  printf("\n");
}

int validar_id(char *str) {
  char *p, s[100];
  long n;

  while (fgets(s, sizeof(s), stdin)) {
    n = strtol(s, &p, 10);
    if (p == s || *p != '\n') {
      puts(str);
    } else
      break;
  }

  return (int)n;
}
