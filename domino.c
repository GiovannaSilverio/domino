#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
    int face1;
    int face2;
    struct no *prox;
} noPeca;

noPeca *priJog1 = NULL; // primeiro elemento da lista do jogador 1
noPeca *priJog2 = NULL; // primeiro elemento da lista do jogador 2
noPeca *priMesa = NULL; // primeiro elemento da lista da mesa

// Função para imprimir as peças de um jogador ou da mesa
void imprime(noPeca *atual) {
    while (atual != NULL) {
        printf("[%d:%d]", atual->face1, atual->face2);
        atual = atual->prox;
    }
    printf("\n");
}

//Inicializa o jogo, distribuindo as peças entre os jogadores e definindo a peça inicial na mesa
int inicializa() {
    int i, j, cont1 = 0, cont2 = 0, sorteador;
    noPeca *novo;
    srand(time(NULL));
    for (i = 0; i < 7; i++) { // face1
        for (j = i; j < 7; j++) { // face2
            novo = (noPeca *)malloc(sizeof(noPeca));
            novo->face1 = i;
            novo->face2 = j;
            novo->prox = NULL;

            // começa a separar as peças aleatoriamente entre os jogadores
            if (cont1 == 14) {
                sorteador = 1;
            } else if (cont2 == 14) {
                sorteador = 0;
            } else {
                sorteador = rand() % 2;
            }

            if ((i == 6) && (j == 6)) {
                // insere a última peça na mesa
                priMesa = novo;
            } else {
                if (sorteador == 0) {
                    // insere na lista do jogador 1
                    novo->prox = priJog1;
                    priJog1 = novo;
                    cont1++;
                } else {
                    // insere na lista do jogador 2
                    novo->prox = priJog2;
                    priJog2 = novo;
                    cont2++;
                }
            }
        }
    }
    return 1; // jogador 1 começa
}

// int inicializa() {
//     int i, j, cont1 = 0, cont2 = 0, sorteador;
//     noPeca *novo;
//     srand(time(NULL));
//     for (i = 0; i < 3; i++) { // face1
//         for (j = i; j < 3; j++) { // face2
//             novo = (noPeca *)malloc(sizeof(noPeca));
//             novo->face1 = i;
//             novo->face2 = j;
//             novo->prox = NULL;

//             // começa a separar as peças aleatoriamente entre os jogadores
//             if (cont1 == 6) {
//                 sorteador = 1;
//             } else if (cont2 == 6) {
//                 sorteador = 0;
//             } else {
//                 sorteador = rand() % 2;
//             }

//             if ((i == 2) && (j == 2)) {
//                 // insere a última peça na mesa
//                 priMesa = novo;
//             } else {
//                 if (sorteador == 0) {
//                     // insere na lista do jogador 1
//                     novo->prox = priJog1;
//                     priJog1 = novo;
//                     cont1++;
//                 } else {
//                     // insere na lista do jogador 2
//                     novo->prox = priJog2;
//                     priJog2 = novo;
//                     cont2++;
//                 }
//             }
//         }
//     }
//     return 1; // jogador 1 começa
// }

// Remove uma peça da lista do jogador 1 que contenha o número `num`
noPeca *removeJogador1(int num) {
    noPeca* atual = priJog1;
    noPeca* anterior = NULL;

    while ((atual != NULL) && (atual->face1 != num && atual->face2 != num)) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            priJog1 = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
    }

    return atual;
}

// Remove uma peça da lista do jogador 2 que contenha o número `num`
noPeca *removeJogador2(int num) {
    noPeca* atual = priJog2;
    noPeca* anterior = NULL;

    while ((atual != NULL) && (atual->face1 != num && atual->face2 != num)) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            priJog2 = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
    }

    return atual;
}

// Insere a peça no início da mesa
void insereInicioMesa(noPeca *peca) {
    if (peca == NULL) return;
    peca->prox = priMesa;
    priMesa = peca;
}

// Insere a peça no final da mesa
void insereFimMesa(noPeca *peca) {
    if (peca == NULL) return;
    noPeca *atual = priMesa;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = peca;
    peca->prox = NULL;
}

// Inverte a face da peça
noPeca *invertePeca(noPeca *peca) {
    int aux = peca->face1;
    peca->face1 = peca->face2;
    peca->face2 = aux;
    return peca;
}

// Imprime o estado atual da mesa e das peças do jogador
void imprimeMenu(int jogador) {
    printf("Mesa: ");
    imprime(priMesa);
    printf("\nJogador %d: ", jogador);
}

// Função principal
int main() {
    int ini = 6, fim = 6;
    int jogador = inicializa();
    noPeca *peca;
    int numEscolhido;

    while (priJog1 != NULL && priJog2 != NULL) {
        imprimeMenu(jogador);
        
        if (jogador == 1) {
            imprime(priJog1);
            printf("Jogador 1, escolha um numero para jogar: ");
            scanf("%d", &numEscolhido);
            peca = removeJogador1(numEscolhido);
        } else {
            imprime(priJog2);
            printf("Jogador 2, escolha um numero para jogar: ");
            scanf("%d", &numEscolhido);
            peca = removeJogador2(numEscolhido);
        }

        if (peca != NULL) {
            if (peca->face1 == ini || peca->face2 == ini) {
                if (peca->face1 == ini) invertePeca(peca);
                insereInicioMesa(peca);
                ini = peca->face1;
            } else if (peca->face1 == fim || peca->face2 == fim) {
                if (peca->face2 == fim) invertePeca(peca);
                insereFimMesa(peca);
                fim = peca->face2;
            } else {
                printf("Jogada invalida! Peca nao combina com as extremidades.\n");
                if (jogador == 1) priJog1 = peca->prox;
                else priJog2 = peca->prox;
            }
        } else {
            printf("Jogador nao possui uma peca com o valor %d.\n", numEscolhido);
        }
        getchar();
        getchar();
        system ("cls");
        jogador = (jogador == 1) ? 2 : 1;
    }

    printf("Jogo terminou! Jogador %d venceu ao eliminar todas as pecas!\n", jogador == 1 ? 2 : 1);
    return 0;
}
