#include "../lib/structs.h"
#include <stdlib.h>
#include <stdio.h>

int matricularAluno(Discente d)
{   
    FILE *arquivo;

    int c; //caractere
    int cont = 0; //contador
    int cpfNoArquivo[11];

    if ((arquivo = fopen(ARQUIVO, "r")) != NULL)
    {
        while (1)
        { // listagem
            c = fgetc(arquivo);
            if ( feof(arquivo) ) break;

            //codigo para pegar cpf
            if (cont < 11)
                cpfNoArquivo[cont] = c;
            cont++;

            if (cont == 11)
            {
                //printf("\n\tVerificando se o CPF existe...");
                int nIguais = 0;
                
                for (int i = 0; i < 11; i++)
                {
                    if (cpfNoArquivo[i] == d.cpf[i])
                    {
                        nIguais++;
                    }
                }

                if (nIguais == 11) {
                    fclose(arquivo);
                    return 1;
                }
            }

            if (c == '\n') cont = 0;
        }

        fclose(arquivo);
    }

    if ((arquivo = fopen(ARQUIVO, "a")) == NULL)
    {
        printf("\n\tNão foi possível abrir o arquivo!");
        return 1;
    }

    for (int i = 0; i < 11; i++)
        fprintf(arquivo, "%c", d.cpf[i]);

    for (int i = 0; d.nome[i] != '\n'; i++)
        fprintf(arquivo, "%c", d.nome[i]);

    fprintf(arquivo, "#%i\n", d.idade);
    
    fclose(arquivo);
        
    return 0;
}