#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa cada cômodo da mansão
typedef struct Sala {
    char nome[50];             // Nome do cômodo
    struct Sala *esquerda;     // Caminho à esquerda
    struct Sala *direita;      // Caminho à direita
} Sala;

// Função que cria uma nova sala dinamicamente
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função que permite o jogador explorar as salas
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Caso a sala não tenha caminhos
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou a um cômodo sem saídas! Fim da exploração.\n");
            break;
        }

        // Mostra as opções disponíveis
        printf("Escolha o caminho:\n");
        if (atual->esquerda != NULL)
            printf("  [e] Ir para %s (esquerda)\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf("  [d] Ir para %s (direita)\n", atual->direita->nome);
        printf("  [s] Sair da exploração\n");

        printf("-> ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("Exploração encerrada pelo jogador.\n");
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função principal: monta o mapa e inicia o jogo
int main() {
    // Montagem da árvore da mansão
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porão");

    // Ligações (estrutura da mansão)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    printf("=== Detective Quest: Exploração da Mansão ===\n");
    printf("Bem-vindo(a) ao jogo! Você começará pelo Hall de Entrada.\n");

    explorarSalas(hall);

    // Liberação da memória (boa prática)
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(porao);

    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}


