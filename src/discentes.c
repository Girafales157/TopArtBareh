#ifndef DISCENTES_C
#define DISCENTES_C

#include <string.h>
#include <ctype.h>
#include "../lib/func.h"
#include "../lib/structs.h"

void matricular() {
    Discente d;
    int continuarLoop = 1;
    char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    while(continuarLoop == 1){
        while(1){
            printf("\n\t[Cadastro de aluno]\n");
            printf("\n\tCPF (somente números): ");
            scanf("%s", &d.cpf); getchar();

            if (strlen(d.cpf) == 11) {
                int deveParar = 0;
                for (int i = 0; i < 11; i++){
                    if (deveParar == 1){
                        system("clear");
                        printf("\tResposta inválida. Tente novamente");
                        break;
                    }

                    for (int j = 0; j < strlen(alfabeto); j++){
                        if (d.cpf[i] == alfabeto[j]){
                            deveParar = 1;
                        }
                    }
                }
                if (deveParar == 0) break;
            } else if (strlen(d.cpf) < 11){
                system("clear");
                printf("\tQuantidade insuficiente de caracteres. Tente novamente");
            } else {
                system("clear");
                printf("\tQuantidade de caracteres excedida. Tente novamente");
            }
            
        }

        while (1)
        {
            printf("\tNome do aluno: ");
            fgets(d.nome, 51, stdin);
            fflush(stdin);

            for (int i = 0; d.nome[i] != '\0'; i++) {
                d.nome[i] = toupper((unsigned char)d.nome[i]);
            }

            if (strlen(d.nome) > 0)
                break;
        }

        while (1)
        {
            printf("\tIdade do aluno: ");
            d.idade = lerSeForInteiro();
            
            if ( d.idade < 121 && d.idade > 0)
                break;
        }

        system("clear");
        continuarLoop = confirmar(d);
        
    }

    system("exit");
}

int confirmar(Discente d){
    char opt[100];

    printf("\n\t[Cadastro de aluno]\n");
    printf("\n\tCPF: ");
    for (int i = 0; i < 11; i++){
        if (i == 3 || i == 6){
            printf(".%c", d.cpf[i]);
        } else if (i == 9){
            printf("-%c", d.cpf[i]);
        } else {
            printf("%c", d.cpf[i]);
        }
    }
    printf("\n\tNome do aluno: %s", d.nome);
    printf("\tIdade do aluno: %i", d.idade);
    
    printf("\n\n\tConfirmar aluno? [S/N]");
    printf("\n\tResposta: ");
    scanf("%s", &opt); getchar();
    
    if (opt[0] == 'S' || opt[0] == 's'){
        int verif = 0;
        if ( (verif = matricularAluno(d)) == 1)
        {
            system("clear");
            printf("------> CPF JÁ EXISTENTE");
            confirmar(d);
        }
        
        return 0;
    }
    if (opt[0] == 'N' || opt[0] == 'n'){
        system("clear");
        return 1;
    } else {
        system("clear");
        printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
        confirmar(d);
    }
}

#endif