#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>
#include <stdlib.h>

// Funções do quicksort
void quick_sort(int *vetor, int inicio, int fim);
void quick_sort_completo(int *vetor, int tamanho);
int particionar(int *vetor, int inicio, int fim);
void trocar(int *vetor, int pos1, int pos2);

#endif