#include "../lib/structs.h"
#include <stdlib.h>
#include <stdio.h>

#define ARQUIVO "alunos.txt"

int matricularAluno(Discente d)
{   
    FILE *arquivo;

    if ((arquivo = fopen(ARQUIVO, "a")) == NULL)
        return 1;

    for (int i = 0; i < 11; i++)
        fprintf(arquivo, "%c", d.cpf[i]);

    for (int i = 0; d.nome[i] != '\n'; i++)
        fprintf(arquivo, "%c", d.nome[i]);

    fprintf(arquivo, "%i\n", d.idade);
    
    fclose(arquivo);
        
    return 0;
}