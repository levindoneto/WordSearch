#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

//Criando a lista(Possui a linha das palavras)
TipoPtNo* cria_lista(void)
{
    return NULL;
}

//void le_dados (TipoInfoNo *dados)
//{
//  printf("Codigo: "); scanf("%d",&dados->codigo);
// printf("Nome: "); scanf("%s",dados->nome);
//printf("Preco: "); scanf("%f",&dados->preco);
//}

/*
retorna 1 se encontrou a linha busca e
retorna 0 caso contrario.
*/

TipoPtNo* insere_ord (TipoPtNo* l, int dados)
{
       TipoPtNo *novo = NULL;                    // Novo elemento na lista
       TipoPtNo *ant = NULL;                     // Ponteiro auxiliar para a posição anterior
       TipoPtNo *ptaux = l;                      // Ponteiro auxiliar para percorrer a lista

       /*Alocando um novo nodo */
       novo = (TipoPtNo*) malloc(sizeof(TipoPtNo));

       /*Insere a informação no novo nodo*/
       novo->linha = dados;


       /*Procurando a posição de inserção*/
       while ((ptaux!=NULL) && (ptaux->linha <= dados))
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }

       /*Fazendo o encadeiamento do elemento*/
       if (ant == NULL) /*O anterior não existe, logo o elemento será inserido na primeira posição*/
       {
             //  puts("inserindo primeiro");
               novo->prox = l;
               l = novo;
       }
       else if(ant->linha == dados )
       {

       }
       else /*elemento inserido no meio da lista*/
       {
            novo->prox = ptaux;
            ant->prox = novo;
       }

       return l;
}


// Funcao usada para imprimir a lista, ou seja as linhas das palavras encontradas
void imprime(TipoPtNo* l,FILE *saida)
{
    TipoPtNo* ptaux;
    if (!l)                           // Caso nao exista a lista
        printf("Lista vazia!\n");
    else
        for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
            fprintf(saida,"%d ",ptaux->linha);
}

TipoPtNo* destroi(TipoPtNo* ptLista)
{
    TipoPtNo *ptaux;                  // Ponteiro auxiliar para percorrer a lista
    while (ptLista != NULL)
    {
        ptaux = ptLista;
        ptLista = ptLista->prox;
        free(ptaux);                  // Desalocando memoria utilizada pela lista
    }
    free(ptLista);
    return NULL;
}
