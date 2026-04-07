#ifndef LISTAGEMB_C
#define LISTAGEMB_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void b(){
    FILE *arqCursos, *arqTurmas;
    
    // fecha o programa se não conseguir ler o arquivo
    if ( (arqCursos = fopen(CURSOS_ARQUIVO, "r")) == NULL ) {
        printf("\n\tArquivo de cursos não encontrado.\n");
        relatorios();
        return;
    }
    if ( (arqTurmas = fopen(TURMAS_ARQUIVO, "r")) == NULL ) {
        printf("\n\tArquivo de turmas não encontrado.\n");
        fclose(arqCursos);
        relatorios();
        return;
    }
    
    printf("\n\t[LISTAGEM: Códigos, nomes, horas, número de vagas e vagas disponíveis dos cursos]\n\n");

    char linhaCurso[1024];
    while (fgets(linhaCurso, sizeof(linhaCurso), arqCursos) != NULL) {
        char codigo[8], nome[60];
        int horas, vagas;
        if (sscanf(linhaCurso, "%7[^#]#%59[^#]#%d#%d", codigo, nome, &horas, &vagas) == 4) {
            // Contar total de alunos matriculados em turmas deste curso
            int totalMatriculados = 0;
            rewind(arqTurmas);
            char linhaTurma[1024];
            while (fgets(linhaTurma, sizeof(linhaTurma), arqTurmas) != NULL) {
                // Parse turma to get codigo and count cpfs
                char *token = strtok(linhaTurma, "#");
                int cpfCount = 0;
                char turmaCodigo[8] = "";
                while ((token = strtok(NULL, "#")) != NULL) {
                    if (strlen(token) == 11) {
                        cpfCount++;
                        token = strtok(NULL, "#"); // skip nota
                    } else {
                        strcpy(turmaCodigo, token);
                        break;
                    }
                }
                if (strcmp(turmaCodigo, codigo) == 0) {
                    totalMatriculados += cpfCount;
                }
            }
            int vagasDisponiveis = vagas - totalMatriculados;
            printf("\t%s | %s | %d horas | %d vagas | %d vagas disponíveis\n", codigo, nome, horas, vagas, vagasDisponiveis);
        }
    }

    printf("\n\tAperte qualquer botão para continuar...");
    int confirmar = getchar();
    
    fclose(arqCursos);
    fclose(arqTurmas);

    relatorios();
}

#endif