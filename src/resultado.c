#ifndef RESULTADO_C
#define RESULTADO_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void resultado(FILE *f, char p[51]){
    // variaveis de controle
    int c; //caractere
    int cont = 0; //contador
    int alunos = 0;

    while (1)
    { // listagem
        c = fgetc(f);
        if ( feof(f) ) break;

        /* //codigo para pegar cpf
        if (cont < 11)
            discente.cpf[cont] = c;
        else 
        */
        if (cont >= 11)
            discente.nome[cont - 11] = c;
        cont++;
        
        if (c == '\n')
        {
            cont = 0;
            //verificar se a palavra existe no nome antes de imprimir o nome na tela
            //printf("%ld", ( strstr(discente.nome, p) - discente.nome ));
            if (( strstr(discente.nome, p) - discente.nome ) >= 0)
            {
                alunos++;
                printf("\t");
                for (int i = 0; discente.nome[i] != '#'; i++)
                {
                    printf("%c", discente.nome[i]);
                    if (discente.nome[i-1] == '#')
                    {
                        break;
                    }
                }
                printf("\n");
            }
        }   
    }
    printf("\n\t%i Alunos encontrados\n\n", alunos);
}


#endif