#ifndef CADASTRO_H
#define CADASTRO_H

void matricular();
int confirmar(Discente d);
void editarAluno();

void criarCurso();
void editarCurso();
void extinguirCurso();

void criarTurma();
void editarTurma();
void extinguirTurma();

#include "../src/cadastro.c"

#endif