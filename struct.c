// Este ficheiro cria e inicializa a struct Livro
// Támbem cria uma instância do tipo Livro chamado 'livro'

struct Livro {
  int id;
  char titlo[50];
  char autor[50];
  char descricao[200];
  char data_pub[10];
} livro;

typedef struct Livro Livro;
