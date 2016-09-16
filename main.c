#include <stdio.h>
#include <string.h>
#include <time.h>
#include "estrutura.h"
#include <locale.h>    /* Biblioteca necessária para uso de configurações regionais. */

int main()
{
    clock_t Ticks[2];

    FILE *texto;        //Arquivo com texto para indexação.
    FILE *consulta;     //Arquivo que contém as palavras para consulta.
    FILE *saida;        //Arquivo para saida dos resultados
    char palavra[25] = {' '} ;
    char ch;
    int i = 0, linha = 1;
    int *ok = 0;
    pNodoA *raiz = NULL;
    pNodoA* a = raiz;
    TipoPtNo *lista=NULL;
    TNodoA *achou = NULL;

// Abre os arquivos para leitura e escrita
    texto = fopen("in.txt","r");
    consulta = fopen("find.txt","r");
    saida = fopen("out.txt","w");


	if((texto != NULL) && (consulta != NULL))
	{
        // Se deu tudo certo com os arquivos
		printf("Arquivos ok..\n");

		while((ch=fgetc(texto))!= EOF)
        {
        // Comparações dentro do arquivo, para reconhecer so' as palavras e nao pegar simbolos juntos
            if(ch == ' ' || ch == '.' || ch == ',' || ch == ';' || ch == '!' || ch == '?' || ch == '"' || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '=' || ch == '&' || ch == '|')
            {
                i=0;
                // Inserindo na AVL
                raiz = InsereAVL(raiz, palavra, &ok,linha);
                // Zera o array palavra
                memset(palavra,(char)0,sizeof(char)*25);
            }
            else
            {
                // Se encontra quebra de linha, incrementa o contador de linhas
                if(ch == '\n')
                {
                     linha++;
                }
                // Deixando todas letras minusculas para fazer as comparacoes
                ch = tolower(ch);
                // Salvando o que está achando no texto no vetor de caracteres(palavra)
                palavra[i] = ch;
                i++;
            }
        }


        Ticks[0] = clock();               // Iniciando o contador de tempo
        // Vai fazendo comparacoes até chegar no final do arquivo aberto
        while((ch=fgetc(consulta))!= EOF)
        {
            i=0;
            while(ch != '\n')
            {
                ch = tolower(ch);
                palavra[i] = ch;
                // Comparacao direta, sem uso de estrutura auxiliar para fazer comparacoes, fazendo economia de tempo
                ch=fgetc(consulta);
                i++;
            }
            palavra[i] = '\0';    //String deve ser terminada com \0
                // achou recebe o retorno da palavra consultada
                achou = consultar(raiz,palavra);
                if(achou)
                {
                    achou->dir = NULL;
                    achou->esq = NULL;
                    imprimeAVL(achou,saida);
                }
                else
                {
                    // Em caso de percorrer todo o arquivo a palavra procurada
                    fprintf(saida,"Consulta: %-10s Palavra não encontrada\n",palavra);
                }
                // Zera o vetor de caracteres (palavra)
                memset(palavra,(char)0,sizeof(char)*25);
            }
             // Fecha o contador de tempo
             Ticks[1] = clock();

             double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
             // Exibe o tempo gasto com a consulta
             fprintf(saida," \n Tempo gasto: %g ms.", Tempo);

            // Fechamento dos arquivos utilizados ao longo da execução do programa
            fclose(consulta);
            fclose(texto);
            fclose(saida);
            // Desalocando a memória utilizada pela árvore
            DestroiAvl(raiz);
	}
	else
	{
        // Em caso de nao conseguir ler os arquvios do disco
		printf("Erro ao realizar a leitura dos arquivos...\n");
	}

return(0);
}
