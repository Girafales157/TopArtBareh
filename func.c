#ifndef FUNC_C
#define FUNC_C

#include <stdio.h>
#include <stdlib.h>

void menu(){
    long i; // input

    system("clear");
    printf("\n\tSistema GAY da TopArtBaré\n");
    printf("\t==================================================\n");
    printf("\t1. Discentes\n");
    printf("\t2. Cursos\n");
    printf("\t3. Turmas\n");
    printf("\t4. Relatórios\n");
    printf("\t0. Sair\n");
    printf("\t==================================================\n");
    printf("\tEscolha: ");
    i = lerSeForInteiro();

    system("clear");

    switch (i){
        case 1:
            discentes();
            break;
        case 2:
            cursos();
            break;
        case 3:
            turmas();
            break;
        case 4:
            relatorios();
            break;
        case 0:
            char opt;
            printf("\n\n\tVocê tem certeza de que deseja sair? [S/N]");
            printf("\n\tResposta: ");
            scanf("%c", &opt);
            if (opt == 'S' || opt == 's' || opt == '0'){
                system("clear");
                system("exit");
            } else {
                system("clear");
                menu();
            }
            break;
        default:
            printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
            menu();
    }
}

void discentes(){
    long i; // input

    system("clear");
    
    printf("\n\tDiscente\n");
    printf("\t==================================================\n");
    printf("\t1. Matricular aluno\n");
    printf("\t2. Editar dados do aluno\n");
    printf("\t3. Eliminar aluno\n");
    printf("\t0. Voltar\n");
    printf("\t==================================================\n");
    printf("\tEscolha: ");
    i = lerSeForInteiro();

    system("clear");

    switch (i){
        case 0:
            menu();
            break;
        default:
            printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
            discentes();
    }
}

void cursos(){
    long i; // input

    system("clear");
    
    printf("\n\tCursos\n");
    printf("\t==================================================\n");
    printf("\t1. Criar curso\n");
    printf("\t2. Editar dados do curso\n");
    printf("\t3. Extinguir curso\n");
    printf("\t0. Voltar\n");
    printf("\t==================================================\n");
    printf("\tEscolha: ");
    i = lerSeForInteiro();

    system("clear");

    switch (i){
        case 0:
            menu();
            break;
        default:
            printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
            cursos();
    }
}

void turmas(){
    long i; // input

    system("clear");
    
    printf("\n\tTurmas\n");
    printf("\t==================================================\n");
    printf("\t1. Criar turma\n");
    printf("\t2. Editar turma\n");
    printf("\t3. Eliminar turma\n");
    printf("\t0. Voltar\n");
    printf("\t==================================================\n");
    printf("\tEscolha: ");
    i = lerSeForInteiro();
    
    system("clear");

    switch (i){
        case 0:
            menu();
            break;
        default:
            printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
            turmas();
    }
}

void relatorios(){
    long i; // input

    system("clear");
    
    /*
    a. Listagem do cpf, nome e idade dos discentes.
    b. Listagem dos códigos, nomes, horas e número de vagas dos cursos.
    c. Listagem de todos os discentes a partir de uma palavra do nome.
    d. Listagem do número da turma, cpf, nome e nota do discente.
    e. Listagem dos números das turmas, cpf, nome e nota do discente, bem como o código
    e nome do curso.
    f. Listagem do cpf, nome e nota do discente conforme o número da turma.
    g. Listagem de todas as turmas, bem como a média das notas dos discentes.
    */
    printf("\n\tRelatórios\n");
    printf("\t==================================================\n");
    printf("\t1. Listagem do cpf, nome e idade dos discentes.\n");
    printf("\t2. Listagem dos códigos, nomes, horas e número de\n\t   vagas dos cursos.\n");
    printf("\t3. Listagem de todos os discentes a partir de uma\n\t   palavra do nome.\n");
    printf("\t4. Listagem do número da turma, cpf, nome e nota\n\t   do discente.\n");
    printf("\t5. Listagem dos números das turmas, cpf, nome e\n\t   nota do discente, bem como o código e nome\n\t   do curso.\n");
    printf("\t6. Listagem do cpf, nome e nota do discente\n\t   conforme o número da turma.\n");
    printf("\t7. Listagem de todas as turmas, bem como a média\n\t   das notas dos discentes.\n");
    printf("\t0. Voltar\n");
    printf("\t==================================================\n");
    printf("\tEscolha: ");
    i = lerSeForInteiro();

    system("clear");

    switch (i){
        case 0:
            menu();
            break;
        default:
            printf("------> RESPONDA APENAS COM AS OPÇÕES NA TELA");
            relatorios();
    }
}

long lerSeForInteiro(){
    char bufferEntrada[64];
    char* onde_a_funcao_de_conversao_parou;

    while (1) {
        fgets(bufferEntrada, 64, stdin);
        long numero = strtol(bufferEntrada, &onde_a_funcao_de_conversao_parou, 0);

        /* Se o número resultante é zero e o ponteiro que aponta para o caractere da string
         * no final da conversão não andou é porque não ocorreu conversão, ou seja, falhou. Além disso, o caractere onde a conversão parou
         * tem que ser uma quebra de linha, caso contrário há caracteres não numéricos
         * que foram ignorados pelo strtol, o que significa que a entrada 
         * não possui somente números.
         */
        if ((numero == 0 && onde_a_funcao_de_conversao_parou == bufferEntrada)
            || *onde_a_funcao_de_conversao_parou != '\n') {
            continue;
        } else {
            return numero;
        }
    }
}

#endif