// Ficheiro principal
#include <locale.h>

// custom
#include "extra_functions.c"

// nome do ficheiro
const char *NOME_FIC = "livros.bin";

// pointer do ficheiro
FILE *file;

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

int main() {
  setlocale(LC_ALL, "");

  if ((file = fopen(NOME_FIC, "ab+")) == NULL) {
    puts("Não foi possível abrir o ficheiro \n");
  }

  fclose(file);
  menu();

  return 0;
}

//
void menu() {

  do {
    int op = 0;

    printf("\n\t MENU\n");

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

//
int pesquisar() {

  limpar();
  printf("\t PESQUISAR\n");

  int idNum;
  int check = 0;

  file = fopen(NOME_FIC, "rb");
  if (file == NULL) {
    puts("Erro ao ler o ficheiro");
    return 1;
  }

  idNum = validar_id("\nIntroduza o id válido do livro: ");

  while (fread(&livro, sizeof(Livro), 1, file)) {
    if (idNum == livro.id) {
      check = 1;
      break;
    }
  }
  printf("\n");

  if (check) {
    printf("\n#############################################\n");
    mostrar_livro(livro);
  } else
    printf("ERRO: O id não existe\n");

  fclose(file);
  return 0;
}

//
int inserir() {

  limpar();
  printf("\t INSERIR\n");

  file = fopen(NOME_FIC, "ab+");
  char c;
  int id;

  if (file == NULL) {
    puts("ERRO: Não foi possível abrir o ficheiro\n");
    return 0;
  }

  id = validar_id("\nIntroduza um id válido do livro: ");

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

  printf("\n\nLivro inserido.\n");

  return 0;
}

//
int listar() {

  limpar();
  printf("\t LISTAR\n");

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
  printf("\n#############################################\n");

  while (fread(&livro, sizeof(Livro), 1, file)) {
    mostrar_livro(livro);
  }

  fclose(file);
  return 0;
}

//
int eliminar() {

  limpar();
  printf("\t ELIMINAR\n");

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

  id = validar_id("\n\nIntroduza um id válido do livro que deseja eliminar: ");

  while (fread(&livro, sizeof(Livro), 1, file)) {

    if (id == livro.id) {

      printf("\n#############################################");
      mostrar_livro(livro);

      found = confirmar_escolha("\nDeseja eliminar este livro? (S/n): ");

      if (found == 1)
        printf("\nREGISTO ELIMADO! \n");

    } else
      fwrite(&livro, sizeof(Livro), 1, file_temp);
  }

  if (!found) {
    printf("\nERRO: Não foi possível encontrar este id: %i\n", id);
  }

  if (found == 2) {
    printf("\nO livro NÃO FOI ELIMINADO.\n");
    remove("temp.bin");
    return 2;
  }

  fclose(file);
  fclose(file_temp);

  remove(NOME_FIC);
  rename("temp.bin", NOME_FIC);

  return 0;
}

//
int atualizar() {

  limpar();
  printf("\t ATUALIZAR\n");

  int id;
  int found = 0;
  char resp, c;

  file = fopen(NOME_FIC, "rb+");
  if (file == NULL) {
    printf("ERRO: Não foi possível ler o ficheiro\n");
    return 0;
  }

  id = validar_id("\nQual é o id do livro que deseja atualizar?\n");

  while (fread(&livro, sizeof(Livro), 1, file)) {

    if (livro.id == id) {

      printf("\n#############################################\n");
      mostrar_livro(livro);

      if (confirmar_escolha("\nDeseja atualizar este livro? (S/n): ") == 1) {
        found = 1;

        id = validar_id("\nDigite um novo id válido: ");
        livro.id = id;

        printf("\n\nPS: Caso NÃO queira mudar um dos campos, deixe-o vazio, ou "
               "seja clique apenas no 'Enter'\n\n");

        printf("Introduza o novo titulo do livro: ");
        atualizar_valor(livro.titlo, 50);

        printf("Introduza o novo nome do autor: ");
        atualizar_valor(livro.autor, 50);

        printf("Introduza uma nova descrição do livro: ");
        atualizar_valor(livro.descricao, 200);

        printf("Introduza a nova data de publicação: ");
        atualizar_valor(livro.data_pub, 10);

        fseek(file, -sizeof(Livro), 1);

        // Esccreve no ficheiro
        fwrite(&livro, sizeof(Livro), 1, file);
        break;
      }
    }
  }

  if (found)
    printf("\nLIVRO ALTERADO COM SUCESSO! \n");

  else
    printf("\nERRO: este id não existe\n");

  fclose(file);
  return 0;
}
