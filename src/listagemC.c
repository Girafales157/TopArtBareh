#ifndef LISTAGEM_C
#define LISTAGEM_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void c(){
    FILE *arq;
    char palavra[51];
    char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char numerosNaturais[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};


    // fecha o programa se não conseguir ler o arquivo
    if ( (arq = fopen(ARQUIVO, "r")) == NULL ) system("exit");

    /* O QUE TÁ FALTANDO: 
        - Fazer com que a linha inteira onde aquele nome se encontra seja lida;
        - Formatar os dados;
        - Repetir e reformular este código em todas as outras listagens;
        - Também preciso impedir que outro aluno se matricule com alguém de mesmo CPF;
    */
    
    while (1)
    {
        printf("\n\t[LISTAGEM: Nome]\n");
        printf("\n\tEscreva uma palavra do nome: ");
        scanf("%s", &palavra); getchar();
        printf("\n");

        //transforma tudo em maiúsculas
        for (int p = 0; palavra[p] != '\0'; p++)
            palavra[p] = toupper((unsigned char)palavra[p]); // unsigned char para ter espaço suficiente para caracteres especiais

        if (strlen(palavra) > 0)
            break;
    }

    resultado(arq, palavra);

    printf("\n\tAperte qualquer botão para continuar...");
    int confirmar = getchar();
    
    fclose(arq);

    relatorios();
}

#endif