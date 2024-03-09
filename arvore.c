// arvore.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

void inicializarFila(Fila *fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

void enfileirarIrmao(Fila *fila, Pessoa *irmao) {
    if (fila->tras == NULL) {
        inicializarFila(fila);
    }

    Node *novoNode = (Node *)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro ao alocar memória para o nó da fila.\n");
        exit(EXIT_FAILURE);
    }

    novoNode->pessoa = irmao;
    novoNode->prox = NULL;

    if (fila->tras == NULL) {
        fila->frente = novoNode;
        fila->tras = novoNode;
    } else {
        fila->tras->prox = novoNode;
        fila->tras = novoNode;
    }
}

void adicionarIrmao(Fila *irmaos, Pessoa *irmao) {
    enfileirarIrmao(irmaos, irmao);
}

void imprimirIrmaos(Fila *irmaos, const char *nomePessoa) {
    if (irmaos != NULL && irmaos->frente != NULL) {
        Node *atual = irmaos->frente;
        while (atual != NULL) {
            printf("Irmão de %s: %s\n", nomePessoa, atual->pessoa->nome);
            atual = atual->prox;
        }
    } else {
        printf("%s não tem irmãos.\n", nomePessoa);
    }
}

int calcularTamanhoArvore(ListaPessoas *lista) {
    int tamanho = 0;
    ListaPessoas *temp = lista;
    while (temp != NULL) {
        tamanho++;
        temp = temp->proximo;
    }
    return tamanho;
}

void removerPessoa(ListaPessoas **lista, const char *nome) {
    ListaPessoas *atual = *lista;
    ListaPessoas *anterior = NULL;

    while (atual != NULL && strcmp(atual->pessoa->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Pessoa com o nome %s não encontrada na lista.\n", nome);
        return;
    }

    Node *nodeAtual = atual->pessoa->irmaos->frente;
    while (nodeAtual != NULL) {
        Node *temp = nodeAtual;
        nodeAtual = nodeAtual->prox;
        free(temp);
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual->pessoa->irmaos);
    free(atual->pessoa);
    free(atual);

    printf("Pessoa removida com sucesso!\n");
}

Pessoa *criarPessoa(const char *nome, Pessoa *pai, Pessoa *mae) {
    Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));
    strcpy(novaPessoa->nome, nome);
    novaPessoa->pai = pai;
    novaPessoa->mae = mae;
    novaPessoa->irmaos = (Fila *)malloc(sizeof(Fila));
    inicializarFila(novaPessoa->irmaos);
    return novaPessoa;
}

void adicionarPessoa(ListaPessoas **lista, Pessoa *pessoa) {
    ListaPessoas *novoNode = (ListaPessoas *)malloc(sizeof(ListaPessoas));
    novoNode->pessoa = pessoa;
    novoNode->proximo = *lista;
    *lista = novoNode;
}

void exibirArvoreGenealogica(Pessoa *pessoa, int nivel) {
    if (pessoa != NULL) {
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("%s", pessoa->nome);

        if (pessoa->irmaos != NULL && pessoa->irmaos->frente != NULL) {
            Node *atual = pessoa->irmaos->frente;
            printf(" - Irmãos - ");
            while (atual != NULL) {
                printf("%s ", atual->pessoa->nome);
                atual = atual->prox;
            }
        }

        printf("\n");

        exibirArvoreGenealogica(pessoa->pai, nivel + 1);
        exibirArvoreGenealogica(pessoa->mae, nivel + 1);
    }
}

Pessoa *buscarPessoa(Pessoa *raiz, const char *nome) {
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }

    Pessoa *pessoaEncontrada = buscarPessoa(raiz->pai, nome);
    if (pessoaEncontrada == NULL) {
        pessoaEncontrada = buscarPessoa(raiz->mae, nome);
    }

    return pessoaEncontrada;
}

void liberarMemoria(ListaPessoas *lista) {
    while (lista != NULL) {
        ListaPessoas *temp = lista;
        lista = lista->proximo;
        free(temp->pessoa->irmaos);
        free(temp->pessoa);
        free(temp);
    }
}

void imprimirIrmaosEFamilia(Pessoa *pessoa) {
    if (pessoa != NULL) {
        printf("Família de %s:\n", pessoa->nome);
        printf("  Pai: %s\n", (pessoa->pai != NULL) ? pessoa->pai->nome : "Desconhecido");
        printf("  Mãe: %s\n", (pessoa->mae != NULL) ? pessoa->mae->nome : "Desconhecido");
        printf("  Irmãos: ");

        if (pessoa->irmaos != NULL && pessoa->irmaos->frente != NULL) {
            Node *atual = pessoa->irmaos->frente;
            while (atual != NULL) {
                printf("%s ", atual->pessoa->nome);
                atual = atual->prox;
            }
        } else {
            printf("Nenhum irmão");
        }

        printf("\n");
    } else {
        printf("Pessoa não encontrada.\n");
    }
}

int calcularAlturaArvore(Pessoa *raiz) {
    if (raiz == NULL) {
        return -1;
    }

    int alturaPai = calcularAlturaArvore(raiz->pai);
    int alturaMae = calcularAlturaArvore(raiz->mae);

    return 1 + ((alturaPai > alturaMae) ? alturaPai : alturaMae);
}
