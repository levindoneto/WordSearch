#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "estrutura.h"
#include <locale.h>    /* Biblioteca necessária para uso de configurações regionais. */

int le_arquivo(char palavra[15])
{
	char url[]="texto.txt";
	char ch;
	int *pt;
	char file_name[50];
	int flag = 0, i = 0;

	FILE* saida;
	FILE* texto;

	scanf("%s",&file_name);


	saida = fopen("saida.txt","w");



    setlocale(LC_ALL,"");

	pt = fopen(url, "r");
	if(pt == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
    {
	    while( (ch=fgetc(pt))!= EOF)
        {
            putchar(ch);
           // palavra[i] = ch;
            //i++;

            //if (ch == EOF)
              //  flag = 1;
        }

    }

	fclose(pt);

	return flag;
}
