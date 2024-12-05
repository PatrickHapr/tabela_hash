#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TAMANHO_TABELA 10 

typedef struct Contato {
    char nome[50];
    char telefone[20];
    struct Contato* proximo;
} Contato;

Contato* tabelaHash[TAMANHO_TABELA];

int funcaoHash(char* nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % TAMANHO_TABELA;
}

void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i] = NULL;
    }
}

Contato* criarContato(char* nome, char* telefone) {
    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = NULL;
    return novoContato;
}

void adicionarContato() {
    char nome[50], telefone[20];
    printf("Digite o nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite o telefone: ");
    scanf(" %[^\n]", telefone);

    LARGE_INTEGER inicio, fim, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    int indice = funcaoHash(nome);
    Contato* novoContato = criarContato(nome, telefone);

    novoContato->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoContato;

    QueryPerformanceCounter(&fim);
    double tempoInsercao = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / freq.QuadPart;
    printf("Contato adicionado com sucesso!\n");
    printf("Tempo de insercao: %.15f ms\n", tempoInsercao);
}

void buscarContato() {
    char nome[50];
    printf("Digite o nome para buscar: ");
    scanf(" %[^\n]", nome);

    LARGE_INTEGER inicio, fim, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            QueryPerformanceCounter(&fim);
            double tempoBusca = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / freq.QuadPart;
            printf("Telefone de %s: %s\n", atual->nome, atual->telefone);
            printf("Tempo de busca: %.15f ms\n", tempoBusca);
            return;
        }
        atual = atual->proximo;
    }
    QueryPerformanceCounter(&fim);
    double tempoBusca = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / freq.QuadPart;
    printf("Contato nao encontrado.\n");
    printf("Tempo de busca: %.15f ms\n", tempoBusca);
}

void removerContato() {
    char nome[50];
    printf("Digite o nome para remover: ");
    scanf(" %[^\n]", nome);

    int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];
    Contato* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                tabelaHash[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    printf("Lista de contatos:\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* atual = tabelaHash[i];
        if (atual != NULL) {
            printf("Indice %d:\n", i);
        }
        while (atual != NULL) {
            printf("  Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

int main() {
    inicializarTabela();

    int opcao;
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}