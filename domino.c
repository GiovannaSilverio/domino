#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct no{
 int face1;
 int face2;
 struct no* prox;
} noPeca;
noPeca* priJog1 = NULL; //primeiro elemento da lista do jogador 1
noPeca* priJog2 = NULL;//primeiro elemento da lista do jogador 2
noPeca* priMesa = NULL; //primeiro elemento da lista da mesa

//serve para imprimir as peças do jogador 1, do jogador 2 e da mesa
void imprime(noPeca * atual){
    while(atual !=NULL){
    printf("[%d:%d]", atual->face1, atual->face2);
    atual=atual->prox;
    }
    printf("\n");
}


int inicializa (){
    int i, j, cont1=0,cont2=0, sorteador;
    noPeca* novo;
    srand(time(NULL));
    for(i=0;i<7;i++){ // face1
        for(j=i;j<7;j++){//face 2
            novo = (noPeca *)malloc(sizeof(noPeca));
            novo->face1=i;
            novo->face2=j;
            novo->prox=NULL;
            

            //começa a separar as peças aleatoriamente entre os jogadores
            if(cont1==14){
                sorteador=1;
            }
            else{
                if(cont2==14){
                    sorteador=0;
                }
                else{
                    sorteador=rand()%2;
                }
            }
            if((i==6)&&(j==6)){
                //insere na lista da mesa
                priMesa = novo;
            }
            else{
                if(sorteador==0){
                    //insere na lista do jogador 2
                    novo->prox = priJog1;
                    priJog1 = novo;
                    cont1++;
                }
                else{
                    //insere na lista do jogador 2
                    novo->prox=priJog2;
                    priJog2=novo;
                    cont2++;
                }
            }
    }
    //mostra qual dos dois jogadores está com mais peças
    if(cont1==14){
        return 1;
    }
    else{
        return 2;
    }
}

int main()  {
    inicializa();
    printf("Jogador 1: \n");
    imprime(priJog1);
    printf("\n\nJogador 2: \n");
    imprime(priJog2);
    printf("\n\nMesa: \n");
    imprime(priMesa);

    return 0;

}