// arvore.h
#ifndef ARVORE_H
#define ARVORE_H

typedef struct Node {
    struct Pessoa *pessoa;
    struct Node *prox;
} Node;

typedef struct Fila {
    Node *frente;
    Node *tras;
} Fila;

typedef struct Pessoa {
    char nome[50];
    struct Pessoa *pai;
    struct Pessoa *mae;
    struct Fila *irmaos;
} Pessoa;

typedef struct ListaPessoas {
    Pessoa *pessoa;
    struct ListaPessoas *proximo;
} ListaPessoas;

void inicializarFila(Fila *fila);
void enfileirarIrmao(Fila *fila, Pessoa *irmao);
void adicionarIrmao(Fila *irmaos, Pessoa *irmao);
void imprimirIrmaos(Fila *irmaos, const char *nomePessoa);
int calcularTamanhoArvore(ListaPessoas *lista);
void removerPessoa(ListaPessoas **lista, const char *nome);
Pessoa *criarPessoa(const char *nome, Pessoa *pai, Pessoa *mae);
void adicionarPessoa(ListaPessoas **lista, Pessoa *pessoa);
void exibirArvoreGenealogica(Pessoa *pessoa, int nivel);
Pessoa *buscarPessoa(Pessoa *raiz, const char *nome);
void liberarMemoria(ListaPessoas *lista);
void imprimirIrmaosEFamilia(Pessoa *pessoa);
int calcularAlturaArvore(Pessoa *raiz);

#endif // ARVORE_H
