#ifndef LISTAGEMG_C
#define LISTAGEMG_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/listagem.h"

void g(){
    FILE *arqTurmas;
    
    if ( (arqTurmas = fopen(TURMAS_ARQUIVO, "r")) == NULL ) {
        printf("\n\tArquivo de turmas não encontrado.\n");
        relatorios();
        return;
    }
    
    printf("\n\t[LISTAGEM: Todas as turmas e média das notas dos discentes]\n\n");

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
        
        // Pular cpfs e notas
        int cpfCount = 0;
        float somaNotas = 0.0;
        while ((token = strtok(NULL, "#")) != NULL) {
            if (strlen(token) == 11) {
                cpfCount++;
                token = strtok(NULL, "#"); // nota
                if (token) somaNotas += atof(token);
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
        
        float media = cpfCount > 0 ? somaNotas / cpfCount : 0.0;
        int vagasDisponiveis = 30 - cpfCount;
        printf("\tTurma %d | Código: %s | Ano: %d | Média das notas: %.2f | Discentes: %d | Vagas disponíveis: %d\n", t.numero, t.codigo, t.ano, media, cpfCount, vagasDisponiveis);
    }

    printf("\n\tAperte qualquer botão para continuar...");
    int confirmar = getchar();
    
    fclose(arqTurmas);

    relatorios();
}

#endif