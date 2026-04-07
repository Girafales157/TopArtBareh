#ifndef REMOVER_C
#define REMOVER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/structs.h"
#include "../lib/func.h"

int removerAluno(const char cpf[12]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        return 1;
    }

    FILE *temp = fopen("alunos.tmp", "w");
    if (temp == NULL) {
        fclose(arquivo);
        return 1;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strlen(linha) >= 11 && memcmp(linha, cpf, 11) == 0) {
            encontrado = 1;
            continue;
        }
        fputs(linha, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        remove("alunos.tmp");
        return 1;
    }

    remove(ARQUIVO);
    rename("alunos.tmp", ARQUIVO);
    return 0;
}

void eliminarAluno() {
    char cpfBusca[12];
    char opt[100];

    while (1) {
        printf("\n\t[Eliminar aluno]\n");
        printf("\n\tCPF (somente números): ");
        scanf("%11s", cpfBusca); getchar();

        if (strlen(cpfBusca) == 11) {
            break;
        }
        system("clear");
        printf("\tCPF inválido. Tente novamente\n");
    }

    printf("\n\tConfirmar exclusão do aluno com CPF %s? [S/N]\n", cpfBusca);
    printf("\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (removerAluno(cpfBusca) == 0) {
            system("clear");
            printf("\tAluno excluído com sucesso\n");
        } else {
            system("clear");
            printf("\tAluno não encontrado ou erro ao excluir\n");
        }
    } else {
        system("clear");
        printf("\tExclusão cancelada\n");
    }

    discentes();
}

#endif