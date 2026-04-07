#ifndef LISTAGEMA_C
#define LISTAGEMA_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void a(){
    FILE *arq;
    
    // fecha o programa se não conseguir ler o arquivo
    if ( (arq = fopen(ARQUIVO, "r")) == NULL ) {
        printf("\n\tArquivo de alunos não encontrado.\n");
        relatorios();
        return;
    }
    
    printf("\n\t[LISTAGEM: CPF, nome e idade dos alunos]\n\n");

    // VARIAVEIS DE CONTROLE
    int c; //caractere
    int cont = 0; //contador

    while (1)
    { // listagem
        c = fgetc(arq);
        if ( feof(arq) ) break;

        //codigo para pegar cpf
        if (cont < 11)
            discente.cpf[cont] = c;
        else
            discente.nome[cont - 11] = c;
        cont++;
        
        if (c == '\n')
        {
            printf("\t");

            for (int i = 0; i < 11; i++)
            {
                if (i == 3 || i == 6){
                    printf(".%c", discente.cpf[i]);
                } else if (i == 9){
                    printf("-%c", discente.cpf[i]);
                } else {
                    printf("%c", discente.cpf[i]);
                }
            }
            printf(" | ");
            for (int i = 0; discente.nome[i] != '#'; i++)
            {
                printf("%c", discente.nome[i]);
                if (discente.nome[i-1] == '#')
                {
                    break;
                }
            }

            if (discente.nome[cont - (11 + 1 + 4)] == '#')
            {
                printf(" (%c%c%c anos)", discente.nome[cont - 15], discente.nome[cont - 14], discente.nome[cont - 13]);
            }
            else if (discente.nome[cont - (11 + 1 + 3)] == '#')
            {
                printf(" (%c%c anos)", discente.nome[cont - 14], discente.nome[cont - 13]);
            }
            else if (discente.nome[cont - (11 + 1 + 2)] == '#')
            {
                printf(" (%c anos)", discente.nome[cont - 13]);
            }
            cont = 0;
            printf("\n");
        }
    }

    printf("\n\tAperte qualquer botão para continuar...");
    int confirmar = getchar();
    
    fclose(arq);

    relatorios();
}

#endif