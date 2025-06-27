#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>
#include <stdlib.h>

// Funções públicas da API do QuickSort
void quick_sort(int *vetor, int inicio, int fim);
void quick_sort_completo(int *vetor, int tamanho);
void imprimir_vetor(int *vetor, int tamanho);
int* criar_vetor(int tamanho);
void destruir_vetor(int *vetor);
void preencher_vetor_aleatorio(int *vetor, int tamanho, int min, int max);

// Funções auxiliares (privadas)
int _mediana_tres(int *vetor, int inicio, int meio, int fim);
void _trocar_elementos(int *vetor, int pos1, int pos2);
int _particionar(int *vetor, int inicio, int fim);

#endif