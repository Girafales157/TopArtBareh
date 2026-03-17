#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char cpf[11];
    char nome[40];
    int idade;
} discente;

typedef struct {
    char codigo[8][20]; //todos os códigos da turma 
    char nome[60];
    int horas;
    int vagas;
    int participantes;
} curso;

typedef struct {
    int numero;
    char cpfs[11][50]; //cpfs da turma (máximo de 30 integrantes)
    char codigo[8]; //codigo para identificar o curso da turma
    int ano;
    float nota; //média de nota na turma
    int horas_p; //horas participadas
} turma;

#endif