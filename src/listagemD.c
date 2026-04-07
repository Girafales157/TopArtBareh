#ifndef LISTAGEMD_C
#define LISTAGEMD_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void d(){
    FILE *arqTurmas, *arqAlunos;
    
    if ( (arqTurmas = fopen(TURMAS_ARQUIVO, "r")) == NULL ) {
        printf("\n\tArquivo de turmas não encontrado.\n");
        relatorios();
        return;
    }
    if ( (arqAlunos = fopen(ARQUIVO, "r")) == NULL ) {
        printf("\n\tArquivo de alunos não encontrado.\n");
        fclose(arqTurmas);
        relatorios();
        return;
    }
    
    printf("\n\t[LISTAGEM: Número da turma, cpf, nome e nota do discente]\n\n");

    char linhaTurma[1024];
    while (fgets(linhaTurma, sizeof(linhaTurma), arqTurmas) != NULL) {
        Turma t;
        for (int j = 0; j < 30; j++) {
            t.cpfs[j][0] = '\0';
            t.notas[j] = 0.0f;
        }
        t.codigo[0] = '\0';
        t.ano = 0;
        t.nota = 0.0f;
        t.horas_p = 0;

        char *token = strtok(linhaTurma, "#");
        if (token) t.numero = atoi(token);
        
        int cpfIndex = 0;
        while ((token = strtok(NULL, "#")) != NULL && cpfIndex < 30) {
            if (strlen(token) == 11) {
                strcpy(t.cpfs[cpfIndex], token);
                token = strtok(NULL, "#");
                if (token) {
                    t.notas[cpfIndex] = atof(token);
                    cpfIndex++;
                } else {
                    break;
                }
            } else {
                strcpy(t.codigo, token);
                token = strtok(NULL, "#");
                if (token) t.ano = atoi(token);
                token = strtok(NULL, "#");
                if (token) t.nota = atof(token);
                token = strtok(NULL, "#");
                if (token) t.horas_p = atoi(token);
                break;
            }
        }
        
        // Agora para cada cpf, buscar nome no alunos.txt
        for (int i = 0; i < cpfIndex; i++) {
            rewind(arqAlunos);
            char linhaAluno[1024];
            int encontrou = 0;
            while (fgets(linhaAluno, sizeof(linhaAluno), arqAlunos) != NULL) {
                if ((int)strlen(linhaAluno) > 11) {
                    char cpfArquivo[12];
                    char nome[51];
                    int idade;
                    memcpy(cpfArquivo, linhaAluno, 11);
                    cpfArquivo[11] = '\0';
                    char *nomeInicio = linhaAluno + 11;
                    char *hash = strchr(nomeInicio, '#');
                    if (hash) {
                        int len = hash - nomeInicio;
                        if (len > 50) len = 50;
                        memcpy(nome, nomeInicio, len);
                        nome[len] = '\0';
                        if (sscanf(hash + 1, "%d", &idade) == 1) {
                            if (strcmp(cpfArquivo, t.cpfs[i]) == 0) {
                                printf("\t%d | %s | %s | %.2f\n", t.numero, cpfArquivo, nome, t.notas[i]);
                                encontrou = 1;
                                break;
                            }
                        }
                    }
                }
            }
            if (!encontrou) {
                printf("\t%d | %s | Nome não encontrado | %.2f\n", t.numero, t.cpfs[i], t.notas[i]);
            }
        }
    }

    printf("\n\tAperte qualquer botão para continuar...");
    int confirmar = getchar();
    
    fclose(arqTurmas);
    fclose(arqAlunos);

    relatorios();
}

#endif