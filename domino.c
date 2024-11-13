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
    if(cont1==14){
        return 1; // jogador 1 começa
    }
    else{
        return 2; // jogador 2 começa
    }
}


// Remove a primeira peça da lista do jogador 1 que contenha o número
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

// Remove a primeira peça da lista do jogador 2 que contenha o número 
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

// Calcula a quantidade de peças na mão de um jogador
int contarPecas(noPeca *jogador) {
    int count = 0;
    while (jogador != NULL) {
        count++;
        jogador = jogador->prox;
    }
    return count;
}

// Calcula a soma dos pontos das peças restantes de um jogador
int calcularPontos(noPeca *jogador) {
    int soma = 0;
    while (jogador != NULL) {
        soma += jogador->face1 + jogador->face2;
        jogador = jogador->prox;
    }
    return soma;
}

// Verifica se o jogo está travado (nenhum jogador tem uma peça jogável)
int jogoTravado(int ini, int fim) {
    noPeca *atual;

    // Verifica se o jogador 1 tem alguma peça jogável
    atual = priJog1;
    while (atual != NULL) {
        if (atual->face1 == ini || atual->face2 == ini || atual->face1 == fim || atual->face2 == fim) {
            return 0; // O jogo não está travado, pois jogador 1 pode jogar
        }
        atual = atual->prox;
    }

    // Verifica se o jogador 2 tem alguma peça jogável
    atual = priJog2;
    while (atual != NULL) {
        if (atual->face1 == ini || atual->face2 == ini || atual->face1 == fim || atual->face2 == fim) {
            return 0; // O jogo não está travado, pois jogador 2 pode jogar
        }
        atual = atual->prox;
    }

    // Se nenhum jogador tem uma peça jogável, o jogo está travado
    return 1;
}

// Função para determinar o vencedor em caso de travamento
void determinarVencedorPorTravamento() {
    int pecasJog1 = contarPecas(priJog1);
    int pecasJog2 = contarPecas(priJog2);

    if (pecasJog1 < pecasJog2) {
        printf("Jogo terminou por travamento! Jogador 1 vence com menos pecas restantes.\n");
    } else if (pecasJog2 < pecasJog1) {
        printf("Jogo terminou por travamento! Jogador 2 vence com menos pecas restantes.\n");
    } else {
        // Empate em número de peças, logo determina pelo maior total de pontos
        int pontosJog1 = calcularPontos(priJog1);
        int pontosJog2 = calcularPontos(priJog2);

        if (pontosJog1 > pontosJog2) {
            printf("Jogo terminou por travamento! Jogador 1 vence com maior soma de pontos nas pecas restantes.\n");
        } else if (pontosJog2 > pontosJog1) {
            printf("Jogo terminou por travamento! Jogador 2 vence com maior soma de pontos nas pecas restantes.\n");
        } else {
            printf("Jogo terminou por travamento! Empate absoluto entre os jogadores.\n");
        }
    }
}

// Função main
int main() {
    int ini = 6, fim = 6;
    int jogador = inicializa();
    noPeca *peca;
    int numEscolhido;
    while (priJog1 != NULL && priJog2 != NULL) {
        imprimeMenu(jogador);

        if (jogoTravado(ini, fim)) {
            // O jogo está travado, então determina o vencedor por travamento
            determinarVencedorPorTravamento();
            return 0; // Termina o jogo
        }

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
            // Verifica se a peça pode ser inserida no início ou no fim da mesa
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
                // Reinsere a peça na lista do jogador atual, pois a jogada foi inválida
                if (jogador == 1) {
                    peca->prox = priJog1;
                    priJog1 = peca;
                } else {
                    peca->prox = priJog2;
                    priJog2 = peca;
                }
            }
        } else {
            printf("Jogador nao possui uma peca com o valor %d.\n", numEscolhido);
        }

        // Limpa a tela para o prox jogador
        system("cls");

        // Alterna o jogador
        jogador = (jogador == 1) ? 2 : 1;
    }

    // Caso algum jogador esvazie a mão, ele vence
    printf("Jogo terminou! Jogador %d venceu ao eliminar todas as pecas!\n", jogador == 1 ? 2 : 1);
    return 0;
}
