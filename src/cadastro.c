#ifndef CADASTRO_C
#define CADASTRO_C

#include <string.h>
#include <ctype.h>
#include "../lib/func.h"
#include "../lib/structs.h"

#define CURSOS_ARQUIVO "cursos.txt"

int cadastrarCurso(Curso c);
int confirmarCurso(Curso c);

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
            fgets(d.nome, 47, stdin);
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
            
            if (d.idade < 121 && d.idade > 0)
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

void criarCurso() {
    Curso c;
    int continuarLoop = 1;

    while (continuarLoop == 1) {
        while (1) {
            printf("\n\t[Criação de curso]\n");
            printf("\n\tCódigo do curso: ");
            scanf("%19s", c.codigo[0]); getchar();

            if (strlen(c.codigo[0]) > 0) {
                break;
            }
        }

        while (1) {
            printf("\tNome do curso: ");
            fgets(c.nome, 60, stdin);
            c.nome[strcspn(c.nome, "\n")] = '\0';

            for (int i = 0; c.nome[i] != '\0'; i++) {
                c.nome[i] = toupper((unsigned char)c.nome[i]);
            }

            if (strlen(c.nome) > 0) {
                break;
            }
        }

        while (1) {
            printf("\tHoras do curso: ");
            c.horas = lerSeForInteiro();

            if (c.horas > 0 && c.horas < 10000) {
                break;
            }
        }

        while (1) {
            printf("\tVagas do curso: ");
            c.vagas = lerSeForInteiro();

            if (c.vagas > 0 && c.vagas < 10000) {
                break;
            }
        }

        system("clear");
        continuarLoop = confirmarCurso(c);
    }

    system("exit");
}

int cadastrarCurso(Curso c) {
    FILE *arquivo;
    char linha[256];

    arquivo = fopen(CURSOS_ARQUIVO, "r");
    if (arquivo != NULL) {
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            char codigoExistente[20];
            int i = 0;

            while (linha[i] != '\0' && linha[i] != '#' && i < 19) {
                codigoExistente[i] = linha[i];
                i++;
            }
            codigoExistente[i] = '\0';

            if (strcmp(codigoExistente, c.codigo[0]) == 0) {
                fclose(arquivo);
                return 1;
            }
        }
        fclose(arquivo);
    }

    arquivo = fopen(CURSOS_ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("\n\tNão foi possível abrir o arquivo!");
        return 1;
    }

    fprintf(arquivo, "%s#%s#%i#%i\n", c.codigo[0], c.nome, c.horas, c.vagas);
    fclose(arquivo);

    return 0;
}

int confirmarCurso(Curso c) {
    char opt[100];

    printf("\n\t[Criação de curso]\n");
    printf("\n\tCódigo do curso: %s\n", c.codigo[0]);
    printf("\tNome do curso: %s\n", c.nome);
    printf("\tHoras do curso: %i\n", c.horas);
    printf("\tVagas do curso: %i\n", c.vagas);

    printf("\n\n\tConfirmar curso? [S/N]");
    printf("\n\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (cadastrarCurso(c) == 1) {
            system("clear");
            printf("------> CÓDIGO JÁ EXISTENTE");
            return confirmarCurso(c);
        }
        return 0;
    }
    if (opt[0] == 'N' || opt[0] == 'n') {
        system("clear");
        return 1;
    } else {
        system("clear");
        printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
        return confirmarCurso(c);
    }
}

#endif