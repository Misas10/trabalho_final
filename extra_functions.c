// Neste ficheiro contêm algumas funcões úteis para
// algumas operações realizadas no ficheiro principal main.c
// e que no entanto, não realizam leitura ou escrita na base de dados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.c"

void mostrar_livro(struct Livro str_livro) {
  printf("\n");
  printf("ID: %i \n", str_livro.id);
  printf("AUTOR: %s", str_livro.autor);
  printf("TÍTULO: %s", str_livro.titlo);
  printf("DESCRIÇÃO: %s", str_livro.descricao);
  printf("DATA DE PUBLICAÇÃO: %s", str_livro.data_pub);
  printf("\n#############################################\n");
}

// confima a escolha do utilizador
// retorna 1, se o utilizador quiser avançar com a operação
// e retorna 2, caso contrário
int confirmar_escolha(char *str) {

  puts(str);
  char resp = getchar();

  if (resp == 'S' || resp == 's')
    return 1;

  return 2;
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

// limpa o ecrã ('cls' no Windows, 'clear' no Unix)
void limpar() {
  int sys = system("cls");
  if (sys != 0)
    system("clear");
}
