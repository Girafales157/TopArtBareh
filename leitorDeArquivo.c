#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ARQUIVO "alunos.txt"

int main(int argc, char const *argv[])
{
    FILE *arq;
    int c;
    char flag[51];
    int i = 0;
    char res[51];
    
    if ( (arq = fopen(ARQUIVO, "r")) == NULL ) return 1;

    printf("Informe um nome: ");
    scanf("%s", &flag);

    for (int j = 0; flag[j] != '\0'; j++)
        flag[j] = toupper((unsigned char)flag[j]);
    
    while (1)
    { // TENTAR ENCONTRAR UM NOME ESPECÍFICO
        c = fgetc(arq);
        if ( feof(arq) ) break;
        if (c == flag[i])
        {
            res[i] = c;
            i++;

            if ( (i) == strlen(flag) )
                printf("%s\n", res);

        } else i = 0;
        
    }
    

    fclose(arq);

    return 0;
}
