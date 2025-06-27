#include "quicksort.h"

// Função principal do quicksort (sua implementação corrigida)
void quick_sort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int pivo_pos = _particionar(vetor, inicio, fim);
        quick_sort(vetor, inicio, pivo_pos - 1);
        quick_sort(vetor, pivo_pos + 1, fim);
    }
}

// Versão simplificada para o usuário (só precisa passar o vetor e tamanho)
void quick_sort_completo(int *vetor, int tamanho) {
    if (vetor != NULL && tamanho > 1) {
        quick_sort(vetor, 0, tamanho - 1);
    }
}

// Função para particionar usando mediana de três
int _particionar(int *vetor, int inicio, int fim) {
    // Usar mediana de três para escolher o pivô
    int meio = (inicio + fim) / 2;
    int pivo = _mediana_tres(vetor, inicio, meio, fim);
    
    // Encontrar a posição do pivô no vetor
    int pivo_pos = inicio;
    if (vetor[meio] == pivo) pivo_pos = meio;
    else if (vetor[fim] == pivo) pivo_pos = fim;
    
    // Colocar o pivô no final temporariamente
    _trocar_elementos(vetor, pivo_pos, fim);
    pivo_pos = fim;
    
    int i = inicio - 1;
    
    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            _trocar_elementos(vetor, i, j);
        }
    }
    
    // Colocar o pivô na posição correta
    _trocar_elementos(vetor, i + 1, pivo_pos);
    return i + 1;
}

// Sua função mediana de três (corrigida)
int _mediana_tres(int *vetor, int inicio, int meio, int fim) {
    int start = vetor[inicio];
    int mid = vetor[meio];  
    int end = vetor[fim];

    if ((start <= mid && mid <= end) || (end <= mid && mid <= start)) {
        return mid;
    } else if ((mid <= start && start <= end) || (end <= start && start <= mid)) {
        return start;
    } else {
        return end;
    }
}

// Função auxiliar para trocar elementos
void _trocar_elementos(int *vetor, int pos1, int pos2) {
    if (pos1 != pos2) {
        int temp = vetor[pos1];
        vetor[pos1] = vetor[pos2];
        vetor[pos2] = temp;
    }
}

// Função para imprimir o vetor
void imprimir_vetor(int *vetor, int tamanho) {
    if (vetor == NULL) {
        printf("Vetor nulo\n");
        return;
    }
    
    printf("Vetor[%d]: [", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("%d", vetor[i]);
        if (i < tamanho - 1) printf(", ");
    }
    printf("]\n");
}

// Função para criar um vetor dinamicamente
int* criar_vetor(int tamanho) {
    if (tamanho <= 0) {
        printf("Erro: Tamanho deve ser maior que 0\n");
        return NULL;
    }
    
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    if (!vetor) {
        printf("Erro: Falha na alocação de memória\n");
        return NULL;
    }
    
    return vetor;
}

// Função para destruir o vetor
void destruir_vetor(int *vetor) {
    if (vetor) {
        free(vetor);
    }
}

// Função para preencher vetor com valores aleatórios
void preencher_vetor_aleatorio(int *vetor, int tamanho, int min, int max) {
    if (vetor == NULL) return;
    
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = min + rand() % (max - min + 1);
    }
}