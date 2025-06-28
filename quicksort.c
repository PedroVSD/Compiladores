#include "quicksort.h"

void quick_sort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int pivo_pos = particionar(vetor, inicio, fim);
        quick_sort(vetor, inicio, pivo_pos - 1);
        quick_sort(vetor, pivo_pos + 1, fim);
    }
}

void quick_sort_completo(int *vetor, int tamanho) {
    if (vetor != NULL && tamanho > 1) {
        quick_sort(vetor, 0, tamanho - 1);
    }
}

int particionar(int *vetor, int inicio, int fim) {
    int pivo = vetor[fim];
    int i = inicio - 1;
    
    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            trocar(vetor, i, j);
        }
    }
    
    trocar(vetor, i + 1, fim);
    return i + 1;
}

void trocar(int *vetor, int pos1, int pos2) {
    if (pos1 != pos2) {
        int temp = vetor[pos1];
        vetor[pos1] = vetor[pos2];
        vetor[pos2] = temp;
    }
}