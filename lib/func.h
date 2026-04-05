#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

/* a. Listagem do cpf, nome e idade dos discentes.
b. Listagem dos códigos, nomes, horas e número de vagas dos cursos.
c. Listagem de todos os discentes a partir de uma palavra do nome.
d. Listagem do número da turma, cpf, nome e nota do discente.
e. Listagem dos números das turmas, cpf, nome e nota do discente, bem como o código
e nome do curso.
f. Listagem do cpf, nome e nota do discente conforme o número da turma.
g. Listagem de todas as turmas, bem como a média das notas dos discentes.*/

void listagemA();
void listagemB();
void listagemC(char s[40]);
void listagemD();
void listagemE();
void listagemF(int n);
void listagemG();

void sair();

void menu();
void discentes();
void cursos();
void turmas();
void relatorios();

long lerSeForInteiro();

int matricularAluno(Discente d);

#include "../src/func.c"
#include "../src/matricular.c"

#endif