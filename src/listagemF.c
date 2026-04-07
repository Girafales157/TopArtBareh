#ifndef LISTAGEMF_C
#define LISTAGEMF_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void f(){
    int numeroTurma;
    printf("\n\t[LISTAGEM: CPF, nome e nota do discente conforme o número da turma]\n");
    printf("\n\tDigite o número da turma: ");
    numeroTurma = lerSeForInteiro();
    
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
    
    Turma t;
    for (int j = 0; j < 30; j++) {
        t.cpfs[j][0] = '\0';
        t.notas[j] = 0.0f;
    }
    t.codigo[0] = '\0';
    t.ano = 0;
    t.nota = 0.0f;
    t.horas_p = 0;
    int encontrouTurma = 0;
    char linhaTurma[1024];
    while (fgets(linhaTurma, sizeof(linhaTurma), arqTurmas) != NULL) {
        char *token = strtok(linhaTurma, "#");
        if (token && atoi(token) == numeroTurma) {
            t.numero = numeroTurma;
            encontrouTurma = 1;
            
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
            break;
        }
    }
    
    if (!encontrouTurma) {
        printf("\n\tTurma não encontrada.\n");
        fclose(arqTurmas);
        fclose(arqAlunos);
        relatorios();
        return;
    }
    
    printf("\n\tDiscentes na turma %d:\n", numeroTurma);
    for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
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
                            printf("\t%s | %s | %.2f\n", cpfArquivo, nome, t.notas[i]);
                            encontrou = 1;
                            break;
                        }
                    }
                }
            }
        }
        if (!encontrou) {
            printf("\t%s | Nome não encontrado | %.2f\n", t.cpfs[i], t.notas[i]);
        }
    }

    printf("\n\tAperte qualquer botão para continuar...");
    int confirmar = getchar();
    
    fclose(arqTurmas);
    fclose(arqAlunos);

    relatorios();
}

#endif