#ifndef CADASTRO_C
#define CADASTRO_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../lib/func.h"
#include "../lib/structs.h"

int cadastrarCurso(Curso c);
int confirmarCurso(Curso c);
int encontrarCursoPorCodigo(const char *codigo, Curso *saida);
int atualizarCurso(Curso novo);
int removerCurso(const char codigo[20]);

int cadastrarTurma(Turma t);
int confirmarTurma(Turma t);
int encontrarTurmaPorNumero(int numero, Turma *saida);
int atualizarTurma(Turma novo);
int removerTurma(int numero);

void matricular() {
    Discente d;
    int continuarLoop = 1;
    char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    while(continuarLoop == 1){
        while(1){
            printf("\n\t[Cadastro de aluno]\n");
            printf("\n\tCPF (somente números): ");
            scanf("%11s", d.cpf); getchar();

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
    discentes();
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
    scanf("%99s", opt); getchar();
    
    if (opt[0] == 'S' || opt[0] == 's'){
        int verif = 0;
        if ( (verif = matricularAluno(d)) == 1)
        {
            system("clear");
            printf("------> CPF JÁ EXISTENTE");
            return confirmar(d);
        }
        
        return 0;
    }
    if (opt[0] == 'N' || opt[0] == 'n'){
        system("clear");
        return 1;
    } else {
        system("clear");
        printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
        return confirmar(d);
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

    cursos();
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

int encontrarAlunoPorCpf(char cpf[12], Discente *saida) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strlen(linha) < 12) continue;
        if (memcmp(linha, cpf, 11) == 0) {
            memcpy(saida->cpf, cpf, 11);
            saida->cpf[11] = '\0';

            char *hash = strchr(linha + 11, '#');
            if (hash == NULL) break;

            int nomeLen = hash - (linha + 11);
            if (nomeLen >= (int)sizeof(saida->nome))
                nomeLen = sizeof(saida->nome) - 1;

            memcpy(saida->nome, linha + 11, nomeLen);
            saida->nome[nomeLen] = '\0';
            saida->idade = atoi(hash + 1);
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

int atualizarAluno(Discente novo) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    FILE *temp = fopen("alunos.tmp", "w");
    if (temp == NULL) {
        fclose(arquivo);
        return 1;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strlen(linha) >= 11 && memcmp(linha, novo.cpf, 11) == 0) {
            fprintf(temp, "%.*s%s#%i\n", 11, novo.cpf, novo.nome, novo.idade);
            encontrado = 1;
        } else {
            fputs(linha, temp);
        }
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

void editarAluno() {
    Discente d;
    char cpfBusca[12];
    char opt[100];
    int continuarLoop = 1;

    while (continuarLoop == 1) {
        while (1) {
            printf("\n\t[Editar aluno]\n");
            printf("\n\tCPF (somente números): ");
            scanf("%11s", cpfBusca); getchar();

            if (strlen(cpfBusca) == 11) {
                break;
            }

            system("clear");
            printf("\tCPF inválido. Tente novamente");
        }

        if (encontrarAlunoPorCpf(cpfBusca, &d) != 0) {
            system("clear");
            printf("\tCPF não encontrado. Tente novamente");
            continue;
        }

        system("clear");
        printf("\n\t[Editar aluno]\n");
        printf("\n\tCPF: ");
        for (int i = 0; i < 11; i++) {
            if (i == 3 || i == 6) {
                printf(".%c", d.cpf[i]);
            } else if (i == 9) {
                printf("-%c", d.cpf[i]);
            } else {
                printf("%c", d.cpf[i]);
            }
        }
        printf("\n\tNome atual: %s\n", d.nome);
        printf("\tIdade atual: %i\n", d.idade);

        while (1) {
            printf("\tNovo nome do aluno: ");
            fgets(d.nome, sizeof(d.nome), stdin);
            d.nome[strcspn(d.nome, "\n")] = '\0';

            for (int i = 0; d.nome[i] != '\0'; i++) {
                d.nome[i] = toupper((unsigned char)d.nome[i]);
            }

            if (strlen(d.nome) > 0)
                break;
        }

        while (1) {
            printf("\tNova idade do aluno: ");
            d.idade = lerSeForInteiro();

            if (d.idade > 0 && d.idade < 121)
                break;
        }

        system("clear");
        printf("\n\t[Editar aluno]\n");
        printf("\n\tCPF: ");
        for (int i = 0; i < 11; i++) {
            if (i == 3 || i == 6) {
                printf(".%c", d.cpf[i]);
            } else if (i == 9) {
                printf("-%c", d.cpf[i]);
            } else {
                printf("%c", d.cpf[i]);
            }
        }
        printf("\n\tNome do aluno: %s\n", d.nome);
        printf("\tIdade do aluno: %i\n", d.idade);

        printf("\n\n\tConfirmar alteração? [S/N]");
        printf("\n\tResposta: ");
        scanf("%99s", opt); getchar();

        if (opt[0] == 'S' || opt[0] == 's') {
            if (atualizarAluno(d) == 0) {
                system("clear");
                printf("\tDados do aluno atualizados com sucesso");
                continuarLoop = 0;
            } else {
                system("clear");
                printf("\tErro ao atualizar o aluno");
                continuarLoop = 1;
            }
        } else if (opt[0] == 'N' || opt[0] == 'n') {
            system("clear");
            continuarLoop = 1;
        } else {
            system("clear");
            printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
            continuarLoop = 1;
        }
    }
    discentes();
}

int encontrarCursoPorCodigo(const char *codigo, Curso *saida) {
    FILE *arquivo = fopen(CURSOS_ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strlen(linha) < 2) continue;

        char codigoExistente[20] = {0};
        int i = 0;
        while (linha[i] != '\0' && linha[i] != '#' && i < 19) {
            codigoExistente[i] = linha[i];
            i++;
        }
        codigoExistente[i] = '\0';

        if (strcmp(codigoExistente, codigo) == 0) {
            strcpy(saida->codigo[0], codigo);

            char *hash1 = strchr(linha, '#');
            if (hash1 == NULL) break;
            char *hash2 = strchr(hash1 + 1, '#');
            if (hash2 == NULL) break;
            char *hash3 = strchr(hash2 + 1, '#');

            int nomeLen = hash2 - (hash1 + 1);
            if (nomeLen >= (int)sizeof(saida->nome)) nomeLen = sizeof(saida->nome) - 1;
            memcpy(saida->nome, hash1 + 1, nomeLen);
            saida->nome[nomeLen] = '\0';

            saida->horas = atoi(hash2 + 1);
            if (hash3 != NULL) {
                saida->vagas = atoi(hash3 + 1);
            } else {
                saida->vagas = 0;
            }

            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

int atualizarCurso(Curso novo) {
    FILE *arquivo = fopen(CURSOS_ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    FILE *temp = fopen("cursos.tmp", "w");
    if (temp == NULL) {
        fclose(arquivo);
        return 1;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char codigoExistente[20] = {0};
        int i = 0;
        while (linha[i] != '\0' && linha[i] != '#' && i < 19) {
            codigoExistente[i] = linha[i];
            i++;
        }
        codigoExistente[i] = '\0';

        if (strcmp(codigoExistente, novo.codigo[0]) == 0) {
            fprintf(temp, "%s#%s#%i#%i\n", novo.codigo[0], novo.nome, novo.horas, novo.vagas);
            encontrado = 1;
        } else {
            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        remove("cursos.tmp");
        return 1;
    }

    remove(CURSOS_ARQUIVO);
    rename("cursos.tmp", CURSOS_ARQUIVO);
    return 0;
}

int removerCurso(const char codigo[20]) {
    FILE *arquivo = fopen(CURSOS_ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    FILE *temp = fopen("cursos.tmp", "w");
    if (temp == NULL) {
        fclose(arquivo);
        return 1;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char codigoExistente[20] = {0};
        int i = 0;
        while (linha[i] != '\0' && linha[i] != '#' && i < 19) {
            codigoExistente[i] = linha[i];
            i++;
        }
        codigoExistente[i] = '\0';

        if (strcmp(codigoExistente, codigo) == 0) {
            encontrado = 1;
            continue;
        }

        fputs(linha, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        remove("cursos.tmp");
        return 1;
    }

    remove(CURSOS_ARQUIVO);
    rename("cursos.tmp", CURSOS_ARQUIVO);
    return 0;
}

void editarCurso() {
    Curso c;
    char codigoBusca[20];
    char opt[100];

    while (1) {
        printf("\n\t[Editar curso]\n");
        printf("\n\tCódigo do curso: ");
        scanf("%19s", codigoBusca); getchar();

        if (strlen(codigoBusca) > 0) break;
        system("clear");
        printf("\tCódigo inválido. Tente novamente\n");
    }

    if (encontrarCursoPorCodigo(codigoBusca, &c) != 0) {
        system("clear");
        printf("\tCurso não encontrado. Tente novamente\n");
        printf("\n\tAperte qualquer botão para continuar...");
        int confirmar = getchar();
        menu();
    }

    system("clear");
    printf("\n\t[Editar curso]\n");
    printf("\n\tCódigo: %s\n", c.codigo[0]);
    printf("\tNome atual: %s\n", c.nome);
    printf("\tHoras atuais: %i\n", c.horas);
    printf("\tVagas atuais: %i\n", c.vagas);

    while (1) {
        printf("\tNovo nome do curso: ");
        fgets(c.nome, sizeof(c.nome), stdin);
        c.nome[strcspn(c.nome, "\n")] = '\0';

        for (int i = 0; c.nome[i] != '\0'; i++) {
            c.nome[i] = toupper((unsigned char)c.nome[i]);
        }

        if (strlen(c.nome) > 0) break;
    }

    while (1) {
        printf("\tNova carga horária: ");
        c.horas = lerSeForInteiro();
        if (c.horas > 0 && c.horas < 10000) break;
    }

    while (1) {
        printf("\tNovo número de vagas: ");
        c.vagas = lerSeForInteiro();
        if (c.vagas > 0 && c.vagas < 10000) break;
    }

    system("clear");
    printf("\n\t[Editar curso]\n");
    printf("\n\tCódigo: %s\n", c.codigo[0]);
    printf("\tNome do curso: %s\n", c.nome);
    printf("\tHoras do curso: %i\n", c.horas);
    printf("\tVagas do curso: %i\n", c.vagas);

    printf("\n\n\tConfirmar alteração? [S/N]");
    printf("\n\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (atualizarCurso(c) == 0) {
            system("clear");
            printf("\tCurso atualizado com sucesso\n");
        } else {
            system("clear");
            printf("\tErro ao atualizar o curso\n");
        }
    } else {
        system("clear");
        printf("\tAlteração cancelada\n");
    }

    cursos();
}

void extinguirCurso() {
    char codigoBusca[20];
    char opt[100];

    while (1) {
        printf("\n\t[Extinguir curso]\n");
        printf("\n\tCódigo do curso: ");
        scanf("%19s", codigoBusca); getchar();

        if (strlen(codigoBusca) > 0) break;
        system("clear");
        printf("\tCódigo inválido. Tente novamente\n");
    }

    printf("\n\tConfirmar extinção do curso %s? [S/N]\n", codigoBusca);
    printf("\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (removerCurso(codigoBusca) == 0) {
            system("clear");
            printf("\tCurso extinto com sucesso\n");
        } else {
            system("clear");
            printf("\tCurso não encontrado ou erro ao extinguir\n");
        }
    } else {
        system("clear");
        printf("\tExtinção cancelada\n");
    }

    cursos();
}

int encontrarTurmaPorNumero(int numero, Turma *saida) {
    FILE *arquivo = fopen(TURMAS_ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int num;
        if (sscanf(linha, "%d#", &num) == 1 && num == numero) {
            saida->numero = num;

            char *token = strtok(linha + strcspn(linha, "#") + 1, "#");
            int index = 0;
            while (token != NULL && index < 30) {
                if (strlen(token) == 11) {
                    strcpy(saida->cpfs[index], token);
                    token = strtok(NULL, "#");
                    if (token) {
                        saida->notas[index] = atof(token);
                        index++;
                    }
                } else {
                    strcpy(saida->codigo, token);
                    token = strtok(NULL, "#");
                    if (token) saida->ano = atoi(token);
                    token = strtok(NULL, "#");
                    if (token) saida->nota = atof(token);
                    token = strtok(NULL, "#");
                    if (token) saida->horas_p = atoi(token);
                    break;
                }
                token = strtok(NULL, "#");
            }

            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

int atualizarTurma(Turma novo) {
    FILE *arquivo = fopen(TURMAS_ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    FILE *temp = fopen("turmas.tmp", "w");
    if (temp == NULL) {
        fclose(arquivo);
        return 1;
    }

    char linha[1024];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int num;
        if (sscanf(linha, "%d#", &num) == 1 && num == novo.numero) {
            fprintf(temp, "%d#", novo.numero);
            for (int i = 0; i < 30 && strlen(novo.cpfs[i]) > 0; i++) {
                fprintf(temp, "%s#%.2f#", novo.cpfs[i], novo.notas[i]);
            }
            fprintf(temp, "%s#%d#%.2f#%d\n", novo.codigo, novo.ano, novo.nota, novo.horas_p);
            encontrado = 1;
        } else {
            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        remove("turmas.tmp");
        return 1;
    }

    remove(TURMAS_ARQUIVO);
    rename("turmas.tmp", TURMAS_ARQUIVO);
    return 0;
}

int removerTurma(int numero) {
    FILE *arquivo = fopen(TURMAS_ARQUIVO, "r");
    if (arquivo == NULL) return 1;

    FILE *temp = fopen("turmas.tmp", "w");
    if (temp == NULL) {
        fclose(arquivo);
        return 1;
    }

    char linha[1024];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int num;
        if (sscanf(linha, "%d#", &num) == 1 && num == numero) {
            encontrado = 1;
            continue;
        }
        fputs(linha, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        remove("turmas.tmp");
        return 1;
    }

    remove(TURMAS_ARQUIVO);
    rename("turmas.tmp", TURMAS_ARQUIVO);
    return 0;
}

void criarTurma() {
    Turma t;
    int continuarLoop = 1;

    // Inicializar cpfs e notas como vazios/0
    for (int i = 0; i < 30; i++) {
        strcpy(t.cpfs[i], "");
        t.notas[i] = 0.0;
    }

    while (continuarLoop == 1) {
        while (1) {
            printf("\n\t[Criação de turma]\n");
            printf("\n\tNúmero da turma: ");
            t.numero = lerSeForInteiro();
            if (t.numero > 0) break;
        }

        while (1) {
            printf("\tCódigo do curso: ");
            scanf("%7s", t.codigo); getchar();
            Curso cursoTemp;
            if (encontrarCursoPorCodigo(t.codigo, &cursoTemp) == 0) {
                break;
            }
            printf("\tCódigo de curso não encontrado. Digite um código válido.\n");
        }

        while (1) {
            printf("\tAno: ");
            t.ano = lerSeForInteiro();
            if (t.ano > 1900 && t.ano < 2100) break;
        }

        while (1) {
            printf("\tHoras de participação: ");
            t.horas_p = lerSeForInteiro();
            if (t.horas_p >= 0) break;
        }

        printf("\tCPFs dos alunos (digite um por linha, vazio para parar):\n");
        int cpfCount = 0;
        while (cpfCount < 30) {
            printf("\tCPF %d: ", cpfCount + 1);
            char input[20];
            fgets(input, sizeof(input), stdin);
            // Remover newline
            input[strcspn(input, "\n")] = 0;
            if (strlen(input) == 0) break;
            // Copiar para t.cpfs[cpfCount] se válido
            strcpy(t.cpfs[cpfCount], input);
            // Validar CPF: deve ter exatamente 11 dígitos numéricos
            int valido = 1;
            if (strlen(t.cpfs[cpfCount]) != 11) valido = 0;
            else {
                for (int j = 0; j < 11; j++) {
                    if (!isdigit(t.cpfs[cpfCount][j])) {
                        valido = 0;
                        break;
                    }
                }
            }
            if (!valido) {
                printf("\tCPF inválido. Deve ter exatamente 11 dígitos numéricos.\n");
                continue;
            }
            // Pedir nota
            while (1) {
                printf("\tNota para %s: ", t.cpfs[cpfCount]);
                scanf("%f", &t.notas[cpfCount]); getchar();
                if (t.notas[cpfCount] >= 0 && t.notas[cpfCount] <= 10) break;
                printf("\tNota deve ser entre 0 e 10.\n");
            }
            cpfCount++;
        }

        // Calcular média da turma a partir das notas individuais
        float somaNotas = 0.0;
        int alunos = 0;
        for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
            somaNotas += t.notas[i];
            alunos++;
        }
        t.nota = (alunos > 0) ? (somaNotas / alunos) : 0.0;

        system("clear");
        continuarLoop = confirmarTurma(t);
    }

    turmas();
}

int cadastrarTurma(Turma t) {
    FILE *arquivo = fopen(TURMAS_ARQUIVO, "r");
    if (arquivo != NULL) {
        char linha[1024];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            int num;
            if (sscanf(linha, "%d#", &num) == 1 && num == t.numero) {
                fclose(arquivo);
                return 1;
            }
        }
        fclose(arquivo);
    }

    arquivo = fopen(TURMAS_ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("\n\tNão foi possível abrir o arquivo!");
        return 1;
    }

    fprintf(arquivo, "%d#", t.numero);
    for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
        fprintf(arquivo, "%s#%.2f#", t.cpfs[i], t.notas[i]);
    }
    fprintf(arquivo, "%s#%d#%.2f#%d\n", t.codigo, t.ano, t.nota, t.horas_p);
    fclose(arquivo);

    return 0;
}

int confirmarTurma(Turma t) {
    char opt[100];

    printf("\n\t[Criação de turma]\n");
    printf("\n\tNúmero: %d\n", t.numero);
    printf("\tCódigo do curso: %s\n", t.codigo);
    printf("\tAno: %d\n", t.ano);
    printf("\tNota média: %.2f\n", t.nota);
    printf("\tHoras de participação: %d\n", t.horas_p);
    printf("\tCPFs dos alunos:\n");
    for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
        printf("\t  %s (nota: %.2f)\n", t.cpfs[i], t.notas[i]);
    }

    printf("\n\n\tConfirmar turma? [S/N]");
    printf("\n\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (cadastrarTurma(t) == 1) {
            system("clear");
            printf("------> NÚMERO JÁ EXISTENTE");
            return confirmarTurma(t);
        }
        return 0;
    }
    if (opt[0] == 'N' || opt[0] == 'n') {
        system("clear");
        return 1;
    } else {
        system("clear");
        printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
        return confirmarTurma(t);
    }
}

void editarTurma() {
    Turma t;
    int numeroBusca;
    char opt[100];

    while (1) {
        printf("\n\t[Editar turma]\n");
        printf("\n\tNúmero da turma: ");
        numeroBusca = lerSeForInteiro();
        if (numeroBusca > 0) break;
        system("clear");
        printf("\tNúmero inválido. Tente novamente\n");
    }

    if (encontrarTurmaPorNumero(numeroBusca, &t) != 0) {
        system("clear");
        printf("\tTurma não encontrada\n");
        turmas();
        return;
    }

    system("clear");
    printf("\n\t[Editar turma]\n");
    printf("\n\tNúmero: %d\n", t.numero);
    printf("\tCódigo atual: %s\n", t.codigo);
    printf("\tAno atual: %d\n", t.ano);
    printf("\tNota atual: %.2f\n", t.nota);
    printf("\tHoras atuais: %d\n", t.horas_p);
    printf("\tCPFs atuais:\n");
    for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
        printf("\t  %s\n", t.cpfs[i]);
    }

    while (1) {
        printf("\tNovo código do curso: ");
        scanf("%7s", t.codigo); getchar();
        Curso cursoTemp;
        if (encontrarCursoPorCodigo(t.codigo, &cursoTemp) == 0) {
            break;
        }
        printf("\tCódigo de curso não encontrado. Digite um código válido.\n");
    }

    while (1) {
        printf("\tNovo ano: ");
        t.ano = lerSeForInteiro();
        if (t.ano > 1900 && t.ano < 2100) break;
    }

    while (1) {
        printf("\tNovas horas de participação: ");
        t.horas_p = lerSeForInteiro();
        if (t.horas_p >= 0) break;
    }

    printf("\tNovos CPFs dos alunos (digite um por linha, vazio para parar):\n");
    // Inicializar cpfs e notas como vazios/0 antes de sobrescrever
    for (int i = 0; i < 30; i++) {
        strcpy(t.cpfs[i], "");
        t.notas[i] = 0.0;
    }
    int cpfCount = 0;
    while (cpfCount < 30) {
        printf("\tCPF %d: ", cpfCount + 1);
        char input[20];
        fgets(input, sizeof(input), stdin);
        // Remover newline
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) break;
        // Copiar para t.cpfs[cpfCount] se válido
        strcpy(t.cpfs[cpfCount], input);
        // Validar CPF: deve ter exatamente 11 dígitos numéricos
        int valido = 1;
        if (strlen(t.cpfs[cpfCount]) != 11) valido = 0;
        else {
            for (int j = 0; j < 11; j++) {
                if (!isdigit(t.cpfs[cpfCount][j])) {
                    valido = 0;
                    break;
                }
            }
        }
        if (!valido) {
            printf("\tCPF inválido. Deve ter exatamente 11 dígitos numéricos.\n");
            continue;
        }
        // Pedir nota
        while (1) {
            printf("\tNota para %s: ", t.cpfs[cpfCount]);
            scanf("%f", &t.notas[cpfCount]); getchar();
            if (t.notas[cpfCount] >= 0 && t.notas[cpfCount] <= 10) break;
            printf("\tNota deve ser entre 0 e 10.\n");
        }
        cpfCount++;
    }

    // Calcular média da turma a partir das notas individuais
    float somaNotas = 0.0;
    int alunos = 0;
    for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
        somaNotas += t.notas[i];
        alunos++;
    }
    t.nota = (alunos > 0) ? (somaNotas / alunos) : 0.0;

    system("clear");
    printf("\n\t[Editar turma]\n");
    printf("\n\tNúmero: %d\n", t.numero);
    printf("\tCódigo do curso: %s\n", t.codigo);
    printf("\tAno: %d\n", t.ano);
    printf("\tNota média: %.2f\n", t.nota);
    printf("\tHoras de participação: %d\n", t.horas_p);
    printf("\tCPFs dos alunos:\n");
    for (int i = 0; i < 30 && strlen(t.cpfs[i]) > 0; i++) {
        printf("\t  %s (nota: %.2f)\n", t.cpfs[i], t.notas[i]);
    }

    printf("\n\n\tConfirmar alteração? [S/N]");
    printf("\n\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (atualizarTurma(t) == 0) {
            system("clear");
            printf("\tTurma atualizada com sucesso\n");
        } else {
            system("clear");
            printf("\tErro ao atualizar a turma\n");
        }
    } else {
        system("clear");
        printf("\tAlteração cancelada\n");
    }

    turmas();
}

void extinguirTurma() {
    int numeroBusca;
    char opt[100];

    while (1) {
        printf("\n\t[Extinguir turma]\n");
        printf("\n\tNúmero da turma: ");
        numeroBusca = lerSeForInteiro();
        if (numeroBusca > 0) break;
        system("clear");
        printf("\tNúmero inválido. Tente novamente\n");
    }

    printf("\n\tConfirmar extinção da turma %d? [S/N]\n", numeroBusca);
    printf("\tResposta: ");
    scanf("%99s", opt); getchar();

    if (opt[0] == 'S' || opt[0] == 's') {
        if (removerTurma(numeroBusca) == 0) {
            system("clear");
            printf("\tTurma extinta com sucesso\n");
        } else {
            system("clear");
            printf("\tTurma não encontrada ou erro ao extinguir\n");
        }
    } else {
        system("clear");
        printf("\tExtinção cancelada\n");
    }

    turmas();
}

#endif