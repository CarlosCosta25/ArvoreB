#ifndef ARVORES_H
#define ARVORES_H

#ifdef __cplusplus
extern "C" {
#endif
//Arvore B*
    #define MM 5
#define M (MM*2/3)
#define FALSE 0
#define TRUE  1
    typedef struct TipoRegistro TipoRegistro;
    typedef struct TipoPagina* TipoApontador;
    typedef struct TipoPagina TipoPagina;
    
void Inicializa(TipoApontador* Apont);//inicializa a arvore
void Pesquisa(TipoRegistro *x, TipoApontador Ap);//pesquisa um dado na arvore
void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir);//insere o dado na posição correta na pagina
void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno);// Chamando funcao insere auxiliar
void ImprimeI(TipoApontador p, int nivel);//função que imprime a arvore por recursão 
void Imprime(TipoApontador p) ;//função principal de impressão da arvore



#ifdef __cplusplus
}
#endif

#endif /* ARVORES_H */

