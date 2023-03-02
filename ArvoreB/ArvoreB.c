#include<stdlib.h>
#include<stdio.h>
# include "Arvores.h"

typedef struct TipoRegistro {
    int Chave;
} TipoRegistro;
typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    int n;
    TipoRegistro r[MM-1];
    TipoApontador p[MM];
    int Folha;
} TipoPagina;


void Inicializa(TipoApontador* Apont) {
    *Apont = NULL;
}

void Pesquisa(TipoRegistro *x, TipoApontador Ap) {
    long i = 1;
    if (Ap == NULL) {
        printf("Tipo Registro nao esta presente na arvore\n");
        return;
    }
    while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave) {
        i++;
    }
    if (x->Chave == Ap->r[i - 1].Chave) {
        *x = Ap->r[i - 1];
        printf("O Registro que voce pesquisou foi: %d\n",Ap->r[i-1]);
        return;
    }
    if (x->Chave < Ap->r[i - 1].Chave) {
        Pesquisa(x, Ap->p[i - 1]);
    } else {
        Pesquisa(x, Ap->p[i]);
    }
}

void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir) {
    short NaoAchouPosicao;
    int k;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao) {
        if (Reg.Chave >= Ap->r[k - 1].Chave) {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1) {
            NaoAchouPosicao = FALSE;
        }
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno) {
    long i = 1;
    long j;
    TipoApontador ApTemp;

    if (Ap == NULL) { //Parada da Recursão
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->n && Reg.Chave > Ap->r[i - 1].Chave) {
        i++;
    } // Percorrendo vetores dos nós para encontrar valor maior (ou igual) que o novo indice
    //TipoApontador ApPai = Ap->p[i];
    if (Reg.Chave == Ap->r[i - 1].Chave) {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }

    if (Reg.Chave < Ap->r[i - 1].Chave) {
        i--;
    } // Como o valor nao é igual, só pode ser maior, entao volta-se uma posição

    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno); // a arvore desce

    if (*Cresceu == FALSE) {
        return;
    }

    if (Ap->n < MM) /* Pagina tem espaco */ {
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno); // Chama insere na página pq tem espaço
        *Cresceu = FALSE;
        return;
    }
    /* Overflow: Pagina tem que ser dividida */
    ApTemp = (TipoApontador) malloc(sizeof (TipoPagina)); // Cria nova pagina pra ser raiz da subarvore que vem do split
    ApTemp->n = 0;
    ApTemp->p[0] = NULL; // Ela começa com zero indices e primeiro filho pra NULL
    if (i < M+1) {
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else{
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    }
    for (j = M +2; j <= MM; j++){
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
    }
    Ap->n = M+1;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap) {
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno); 
    if (Cresceu == TRUE) { 
        ApTemp = (TipoPagina *) malloc(sizeof (TipoPagina)); 
        ApTemp->n = 1; 
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno; 
        ApTemp->p[0] = *Ap; 
        *Ap = ApTemp;
    }
}

void ImprimeI(TipoApontador p, int nivel) {
    long i;
    if (p == NULL) return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++)
        printf("%ld ", (long) p->r[i].Chave);
    putchar('\n');
    nivel++;
    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel);
}

void Imprime(TipoApontador p) {
    int n = 0;
    ImprimeI(p, n);
}

