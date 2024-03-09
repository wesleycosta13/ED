// main.c
#include <stdio.h>
#include <string.h>
#include "arvore.h"

int main() {
    ListaPessoas *lista = NULL;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Criar Pessoa\n");
        printf("2. Exibir Árvore Genealógica\n");
        printf("3. Adicionar Irmão\n");
        printf("4. Imprimir Irmãos\n");
        printf("5. Buscar Pessoa\n");
        printf("6. Remover Pessoa\n");
        printf("7. Calcular Tamanho da Árvore\n");
        printf("8. Calcular Altura da Árvore\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char nome[50];
                printf("Digite o nome da pessoa: ");
                scanf("%s", nome);

                printf("Pessoas disponíveis:\n");
                ListaPessoas *temp = lista;
                while (temp != NULL) {
                    printf("%s\n", temp->pessoa->nome);
                    temp = temp->proximo;
                }

                char nomePai[50], nomeMae[50];
                printf("Digite o nome do pai: ");
                scanf("%s", nomePai);
                printf("Digite o nome da mãe: ");
                scanf("%s", nomeMae);

                Pessoa *pai = NULL, *mae = NULL;
                temp = lista;
                while (temp != NULL) {
                    if (strcmp(temp->pessoa->nome, nomePai) == 0) {
                        pai = temp->pessoa;
                    }
                    if (strcmp(temp->pessoa->nome, nomeMae) == 0) {
                        mae = temp->pessoa;
                    }
                    temp = temp->proximo;
                }

                Pessoa *novaPessoa = criarPessoa(nome, pai, mae);
                adicionarPessoa(&lista, novaPessoa);
                printf("Pessoa criada com sucesso!\n");
                break;
            }
            case 2:
                printf("Árvore Genealógica:\n");
                if (lista != NULL) {
                    exibirArvoreGenealogica(lista->pessoa, 0);
                } else {
                    printf("Árvore genealógica vazia.\n");
                }
                break;
            case 3: {
                char nome[50];
                printf("Digite o nome da pessoa para adicionar como irmão: ");
                scanf("%s", nome);

                ListaPessoas *pessoa = lista;
                while (pessoa != NULL) {
                    if (strcmp(pessoa->pessoa->nome, nome) == 0) {
                        break;
                    }
                    pessoa = pessoa->proximo;
                }

                if (pessoa != NULL) {
                    char nomeIrmao[50];
                    printf("Digite o nome do irmão: ");
                    scanf("%s", nomeIrmao);

                    Pessoa *novoIrmao = criarPessoa(nomeIrmao, pessoa->pessoa->pai, pessoa->pessoa->mae);
                    adicionarIrmao(pessoa->pessoa->irmaos, novoIrmao);
                    printf("Irmão adicionado com sucesso!\n");
                } else {
                    printf("Pessoa com o nome %s não encontrada na lista.\n", nome);
                }
                break;
            }
            case 4: {
                char nomeIrmaos[50];
                printf("Digite o nome da pessoa para imprimir os irmãos: ");
                scanf("%s", nomeIrmaos);

                ListaPessoas *pessoa = lista;
                while (pessoa != NULL) {
                    if (strcmp(pessoa->pessoa->nome, nomeIrmaos) == 0) {
                        break;
                    }
                    pessoa = pessoa->proximo;
                }

                if (pessoa != NULL) {
                    imprimirIrmaos(pessoa->pessoa->irmaos, pessoa->pessoa->nome);
                } else {
                    printf("Pessoa com o nome %s não encontrada na lista.\n", nomeIrmaos);
                }

                break;
            }
            case 5: {
                char nomeBusca[50];
                printf("Digite o nome da pessoa para buscar: ");
                scanf("%s", nomeBusca);

                Pessoa *pessoaEncontrada = buscarPessoa(lista->pessoa, nomeBusca);
                imprimirIrmaosEFamilia(pessoaEncontrada);

                break;
            }
            case 6: {
                char nomeRemover[50];
                printf("Digite o nome da pessoa para remover: ");
                scanf("%s", nomeRemover);

                removerPessoa(&lista, nomeRemover);
                break;
            }
            case 7:
                printf("Tamanho da Árvore: %d pessoa(s)\n", calcularTamanhoArvore(lista));
                break;
            case 8: {
                if (lista != NULL) {
                    int altura = calcularAlturaArvore(lista->pessoa);
                    printf("Altura da Árvore: %d\n", altura);
                } else {
                    printf("Árvore genealógica vazia.\n");
                }
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}
