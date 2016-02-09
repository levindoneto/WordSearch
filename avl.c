#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "estrutura.h"

//***Funcao para consultar as palavras***
pNodoA * consultar(pNodoA *raiz, TipoInfo word)
{

    if(raiz)                   // Se a arvore existe
    {
        //   Vai comparando palavra a palavra com a raiz da arvore e se achar
        // ela vai retornando a mesma.
        if(strcmp(raiz->info,word) == 0)
        {
             return raiz;

        }
        //   Vai procurando de acordo com a ordem alfabetica
        // das palavras (com essa ordem que e' escolhido se
        // vai para a direita ou para a esquerda).
        else if (strcmp(raiz->info,word) > 0)
        {
            consultar(raiz->esq,word);
        }
        else
            consultar(raiz->dir,word);
    }
    else
        // Com esse retorno vai imprimir que a palavra nao existe no arquivo
        // de saida(out.txt).
        return(NULL);
}

// Desalocando memoria utilizada pela AVL
pNodoA* DestroiAvl(pNodoA *raiz)
{
    if(raiz == NULL)
    {
        return (NULL);
    }
    else
    {
        DestroiAvl(raiz->dir);
        DestroiAvl(raiz->esq);
        destroi(raiz->listaLSE);
        free(raiz);
    }
}

// Imprimindo a consulta
void imprimeAVL(pNodoA *raiz,FILE *saida)
{
    if(raiz)
    {
        imprimeAVL(raiz->dir,saida);
        imprimeAVL(raiz->esq,saida);
        fprintf(saida,"Consulta: %-10s Palavra encontrada nas linhas ",raiz->info);
        imprime(raiz->listaLSE,saida);
        fprintf(saida,"\n");
    }

}

//***Indexação das palavras na árvore***
pNodoA* InsereAVL (pNodoA *a, TipoInfo x, int *ok, int linha)
{

    //   Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    // x, a chave a ser inserida e h a altura da árvore */

    TipoPtNo* l;

    //   Caso nao exista nada na arvore, aloca memoria pra ela
    // para inserir as palavras
     if (a == NULL)
     {
     	a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->info, x);
        a->esq = NULL;
        a->dir = NULL;
        a->listaLSE = NULL;
        //   As linhas onde se encontram as palavras ficam nas listas,
        // como a consulta e´ feita diretamente, foi preciso inserir
        // ordenadamente na lista.
        a->listaLSE = insere_ord(a->listaLSE, linha);
        a->FB = 0;
	    *ok = 1;

     }
     else
     // Comparacoes necessarias para a indexação ordenada
     if ( strcmp(x, a->info) < 0 )
     {
		a->esq = InsereAVL(a->esq,x,ok,linha);
        if (*ok)
        {
   		    switch (a->FB) {
        	  case -1:  a->FB = 0; *ok = 0; break;
			  case  0:  a->FB = 1;  break;
			  case  1:  a=Caso1(a,ok); break;
            }
         }
     }
	 else if( strcmp(x, a->info) > 0)
     {
  		    a->dir = InsereAVL(a->dir,x,ok,linha);
            if (*ok)
            {
              switch (a->FB) {
                case  1:  a->FB = 0; *ok = 0; break;
                case  0:  a->FB = -1; break;
			    case -1:  a = Caso2(a,ok); break;
             }
            }
     }

     else
        {
            a->listaLSE = insere_ord(a->listaLSE,linha);
        }

     return a;
}

// Funcao que mede a altura da arvore, para fazer o balanceamento depois
int Altura (pNodoA *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
      return 0;
    else
    {
       Alt_Esq = Altura (a->esq);
       Alt_Dir = Altura (a->dir);
       if (Alt_Esq > Alt_Dir)
         return (1 + Alt_Esq);
       else
         return (1 + Alt_Dir);
     }
}

//   Calculando Fator de Balanceamento da arvore
// com base na função que calcula a altura
// da mesma.
int Calcula_FB(pNodoA *a)
{
    return (Altura(a->esq) - Altura(a->dir));
}

// Desenhando(formando) a arvore
void Desenha(pNodoA *a , int nivel)
{
int x;

 if (a !=NULL)
 {
   for (x=1; x<=nivel; x++);
   if (a->esq != NULL) Desenha(a->esq, (nivel+1));
   if (a->dir != NULL) Desenha(a->dir, (nivel+1));
 }
}

// Fazendo verificações pra ver se a arvore esta'
// como AVL ainda.
int is_avl(pNodoA *a)
{
  int alt_esq, alt_dir;

  if (a!=NULL)
  {
     alt_esq = Altura(a->esq);
     alt_dir = Altura(a->dir);
     return ( (alt_esq - alt_dir <2) && (alt_dir - alt_esq <2) && (is_avl(a->esq)) && (is_avl(a->dir)) );
  }
  else
  return 1;
}

//Rotacoes utilizadas no programa
pNodoA* rotacao_direita(pNodoA *pt){
   pNodoA* ptu;

   ptu = pt->esq;
   pt->esq = ptu->dir;
   ptu->dir = pt;
   pt->FB = 0;
   pt = ptu;
   return pt;
}

pNodoA* rotacao_esquerda(pNodoA *pt){
   pNodoA* ptu;

   ptu = pt->dir;
   pt->dir = ptu->esq;
   ptu->esq = pt;
   pt->FB = 0;
   pt = ptu;
   return pt;
}

pNodoA* rotacao_dupla_direita (pNodoA* pt){
   pNodoA* ptu, *ptv;

   ptu = pt->esq;
   ptv = ptu->dir;
   ptu->dir = ptv->esq;
   ptv->esq = ptu;
   pt->esq = ptv->dir;
   ptv->dir = pt;
   if (ptv->FB== 1)   pt->FB = -1;
      else pt->FB = 0;
   if (ptv->FB == -1)  ptu->FB = 1;
      else ptu->FB = 0;
   pt = ptv;
   return pt;
}

pNodoA* rotacao_dupla_esquerda (pNodoA* pt){
   pNodoA *ptu, *ptv;

   ptu = pt->dir;
   ptv = ptu->esq;
   ptu->esq = ptv->dir;
   ptv->dir = ptu;
   pt->dir = ptv->esq;
   ptv->esq = pt;
   if (ptv->FB == -1) pt->FB = 1;
     else pt->FB = 0;
   if (ptv->FB == 1) ptu->FB = -1;
      else ptu->FB = 0;
   pt = ptv;
   return pt;
}

// Casos de rotação que foram precisos
pNodoA* Caso1 (pNodoA* a , int *ok)
{
   pNodoA *ptu;

	ptu = a->esq;
	if (ptu->FB == 1)
    {
        a = rotacao_direita(a);
     }
    else
    {
        a = rotacao_dupla_direita(a);
    }

    a->FB = 0;
	*ok = 0;
	return a;
}

pNodoA* Caso2 (pNodoA *a , int *ok)
{
    pNodoA *ptu;

	ptu = a->dir;
	if (ptu->FB == -1)
    {
       Desenha(a,1);
       a=rotacao_esquerda(a);
    }
    else
    {
       Desenha(a,1);
       a=rotacao_dupla_esquerda(a);
    }
	a->FB = 0;
	*ok = 0;
	return a;
}
