#include<stdlib.h>
#include<stdio.h>
#include "Arvores.h"

typedef struct TipoRegistro {
    int Chave;
} TipoRegistro;
typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    int n;
    TipoRegistro r[MM - 1];
    TipoApontador p[MM];
    int folha;
} TipoPagina;

int main() {
    TipoRegistro registro;
    TipoApontador apont;
    Inicializa(&apont);
    int op = 1;
    while (op != 0) {
        printf("==========MENU==========\n");
        printf("1-Inserir\n2-Pesquisar\n3-Imprimir\n");
        printf("========================\n");
        printf("\nDigite o que vc deseja fazer:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Digite um numero: ");
                scanf("%d", &registro.Chave);
                Insere(registro, &apont);
                Imprime(apont);
                break;
            case 2:
                printf("Digite a chave que vc desejá buscar: ");
                scanf("%d", &registro.Chave);
                Pesquisa(&registro, apont);
                break;
            case 3:
                Imprime(apont);
                break;
        }
    }
    return (EXIT_SUCCESS);
}